# Fuzzing Report: PHP Parser

## Summary

This report details the process and findings of a fuzzing session targeting the PHP parser. The fuzzing was performed using the `libFuzzer`-based fuzzing framework available in the PHP repository.

## Process

1.  **Build:** PHP was built with fuzzing enabled using `clang-17` and AddressSanitizer, following the instructions in `sapi/fuzzer/README.md`.
2.  **Corpus Generation:** A corpus for the parser fuzzer was generated using the `generate_parser_corpus.php` script. The generated corpus was stored in a temporary directory to avoid issues with the repository's file limits.
3.  **Fuzzing:** The parser fuzzer (`php-fuzz-parser`) was run for 60 seconds with the generated corpus. The `-detect_leaks=0` flag was used to allow the fuzzer to run despite pre-existing memory leaks in the seed corpus.

## Findings

### Memory Leak in PHP Parser

The fuzzer detected a memory leak when parsing the following PHP code snippet:

```php
<?php
class A1 {
    const ?B1 C = null;
}

class A2 extends A1 {
    const ?B2 C = null;
}

?>
```

This input was captured in the file `leak-377a0aedb99159b8843610118ec4a79c51857216`.

The fuzzer produced the following stack trace, which indicates the leak occurs in the lexical scanner (`lex_scan`) and string initialization functions:

```
Direct leak of 64 byte(s) in 2 object(s) allocated from:
    #0 0x55baeacd75b2 in malloc (/app/sapi/fuzzer/php-fuzz-parser+0xad75b2) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #1 0x55baebeb0f6f in tracked_malloc /app/Zend/zend_alloc.c:3036:14
    #2 0x55baec3532a9 in zend_string_alloc /app/Zend/zend_string.h:167:36
    #3 0x55baec3532a9 in zend_string_init /app/Zend/zend_string.h:189:21
    #4 0x55baec3532a9 in lex_scan /app/Zend/zend_language_scanner.l:3171:2
    #5 0x55baebf754fd in zendlex /app/Zend/zend_compile.c:2037:8
    #6 0x55baec316e91 in zendparse /app/Zend/zend_language_parser.c:5570:16
    #7 0x55baec329cb9 in zend_compile /app/Zend/zend_language_scanner.l:599:7
    #8 0x55baec329862 in compile_file /app/Zend/zend_language_scanner.l:658:14
    #9 0x55baeb81ebaa in phar_compile_file /app/ext/phar/phar.c:3325:9
    #10 0x55baeb413236 in opcache_compile_file /app/ext/opcache/ZendAccelerator.c
    #11 0x55baeb410dbb in persistent_compile_file /app/ext/opcache/ZendAccelerator.c:2170:23
    #12 0x55baec410dce in fuzzer_do_request_from_buffer /app/sapi/fuzzer/fuzzer-sapi.c:270:29
    #13 0x55baec41034e in LLVMFuzzerTestOneInput /app/sapi/fuzzer/fuzzer-parser.c:35:2
    #14 0x55baeac1fca4 in fuzzer::Fuzzer::ExecuteCallback(unsigned char const*, unsigned long) (/app/sapi/fuzzer/php-fuzz-parser+0xa1fca4) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #15 0x55baeac1f399 in fuzzer::Fuzzer::RunOne(unsigned char const*, unsigned long, bool, fuzzer::InputInfo*, bool, bool*) (/app/sapi/fuzzer/php-fuzz-parser+0xa1f399) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #16 0x55baeac20f86 in fuzzer::Fuzzer::ReadAndExecuteSeedCorpora(std::vector<fuzzer::SizedFile, std::allocator<fuzzer::SizedFile>>&) (/app/sapi/fuzzer/php-fuzz-parser+0xa20f86) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #17 0x55baeac214a7 in fuzzer::Fuzzer::Loop(std::vector<fuzzer::SizedFile, std::allocator<fuzzer::SizedFile>>&) (/app/sapi/fuzzer/php-fuzz-parser+0xa214a7) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #18 0x55baeac0ebeb in fuzzer::FuzzerDriver(int*, char***, int (*)(unsigned char const*, unsigned long)) (/app/sapi/fuzzer/php-fuzz-parser+0xa0ebeb) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #19 0x55baeac39176 in main (/app/sapi/fuzzer/php-fuzz-parser+0xa39176) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
    #20 0x7f690e0851c9 in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #21 0x7f690e08528a in __libc_start_main csu/../csu/libc-start.c:360:3
    #22 0x55baeac03ab4 in _start (/app/sapi/fuzzer/php-fuzz-parser+0xa03ab4) (BuildId: d8d5be0f35566fa5df2078ffa1e857b38575ed5f)
```

### No Crashes Found

The fuzzer did not find any inputs that caused a crash during the 60-second run.

## Recommendations

- **Fix the Memory Leak:** The memory leak identified by the fuzzer should be investigated and fixed.
- **Extended Fuzzing:** To find more subtle bugs, it is recommended to run the fuzzer for a much longer period (hours or even days). The fuzzer was still discovering new code paths when it was stopped.
- **Fuzz Other Targets:** The PHP fuzzing framework includes several other fuzzing targets (e.g., `unserialize`, `json`, `exif`). These should also be fuzzed to find potential vulnerabilities in other parts of the codebase.
