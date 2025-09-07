<?php
// test.php

// Step 1: Verify the function exists
if (!function_exists('fast_read_file')) {
    die("Error: The 'fast_read' extension is not loaded or the function 'fast_read_file' does not exist.\n" .
        "Please run this script with: php -d extension=./modules/fast_read.so test.php\n");
}
echo "Extension 'fast_read' loaded successfully.\n\n";

// Step 2: Setup test environment
$testDir = __DIR__ . '/test_data';
if (!is_dir($testDir)) {
    mkdir($testDir, 0777, true);
}

$originalFile = $testDir . '/original.txt';
$fileSizeMB = 50; // 50 MB file, to keep test time reasonable
$numCopies = 4;
$filePaths = [];

echo "Creating a {$fileSizeMB}MB test file...\n";
// Create a large string (1MB chunk) and repeat it
$chunk = str_repeat("0123456789abcdef", 65536); // 1MB
$fp = fopen($originalFile, 'w');
for ($i = 0; $i < $fileSizeMB; $i++) {
    fwrite($fp, $chunk);
}
fclose($fp);
echo "Test file created at: {$originalFile}\n";

echo "Creating {$numCopies} copies of the test file...\n";
for ($i = 0; $i < $numCopies; $i++) {
    $copyPath = $testDir . "/copy_{$i}.txt";
    copy($originalFile, $copyPath);
    $filePaths[] = $copyPath;
}
echo "Copies created.\n\n";

// --- Benchmarking ---

// 3. Benchmark standard file_get_contents()
echo "Benchmarking standard file_get_contents()...\n";
$start1 = microtime(true);
$content1 = file_get_contents($originalFile);
$time1 = microtime(true) - $start1;
echo "Time taken: " . number_format($time1, 4) . " seconds\n\n";

// 4. Benchmark concurrent fast_read_file()
echo "Benchmarking concurrent fast_read_file()...\n";
$start2 = microtime(true);
$content2 = fast_read_file($filePaths);
$time2 = microtime(true) - $start2;
echo "Time taken: " . number_format($time2, 4) . " seconds\n\n";


// 5. Verify correctness
echo "Verifying content...\n";
if (strlen($content1) !== strlen($content2)) {
    die("Verification FAILED: Lengths do not match!\n" .
        "Standard read length: " . strlen($content1) . "\n" .
        "Concurrent read length: " . strlen($content2) . "\n");
}

if ($content1 === $content2) {
    echo "Verification PASSED: Contents are identical.\n\n";
} else {
    // To avoid printing huge strings, let's compare hashes if they don't match
    $hash1 = md5($content1);
    $hash2 = md5($content2);
    die("Verification FAILED: Contents do not match. MD5 hashes: {$hash1} (standard) vs {$hash2} (concurrent)\n");
}

// 6. Report results
echo "--- Results ---\n";
echo "Standard read:   " . number_format($time1, 4) . "s\n";
echo "Concurrent read: " . number_format($time2, 4) . "s\n";

if ($time2 > 0 && $time1 > $time2) {
    $speedup = ($time1 / $time2);
    echo "Concurrent read was " . number_format($speedup, 2) . " times faster.\n";
} else if ($time1 < $time2) {
    $slowdown = ($time2 / $time1);
    echo "Concurrent read was " . number_format($slowdown, 2) . " times slower.\n";
} else {
    echo "No significant performance difference.\n";
}

// 7. Cleanup
echo "\nCleaning up test files...\n";
unlink($originalFile);
foreach ($filePaths as $path) {
    unlink($path);
}
rmdir($testDir);
echo "Cleanup complete.\n";

?>
