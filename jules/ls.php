<?php

/**
 * Lists files and directories inside the specified directory.
 *
 * @param string $directory The directory to list. Defaults to the current directory.
 * @return string[] An array of file and directory names.
 */
function ls(string $directory = '.'): array
{
    // Return scandir result directly, or an empty array if it fails.
    return scandir($directory) ?: [];
}
