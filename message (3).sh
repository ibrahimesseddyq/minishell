void test_dir_check(void)
{
    // Setup some test directories and files
    system("mkdir -p testdir/subdir");
    system("mkdir -p testdir/empty");
    system("mkdir -p testdir/noperm");
    system("chmod 444 testdir/noperm");
    system("touch testdir/file.txt");
    system("mkdir -p /tmp/testbash/dir1/dir2");
    system("touch /tmp/testbash/file1");
    
    printf("\n=== Starting Directory Check Tests ===\n\n");

    // 1-10: Basic absolute path tests
    assert_test(check_dir_exist("/"), 1, "Test 1: Root directory");
    assert_test(check_dir_exist("/tmp"), 1, "Test 2: Existing system directory");
    assert_test(check_dir_exist("/nonexistent"), 0, "Test 3: Non-existent absolute path");
    assert_test(check_dir_exist("/tmp/testbash"), 1, "Test 4: Existing created directory");
    assert_test(check_dir_exist("/tmp/testbash/file1"), 1, "Test 5: Existing file absolute path");
    assert_test(check_dir_exist("/tmp/testbash/newfile"), 1, "Test 6: New file in existing directory");
    assert_test(check_dir_exist("/tmp/testbash/dir1/dir2"), 1, "Test 7: Nested existing directories");
    assert_test(check_dir_exist("/tmp/testbash/dir1/dir2/newfile"), 1, "Test 8: New file in nested directory");
    assert_test(check_dir_exist("/tmp/testbash/nonexistent/file"), 0, "Test 9: File in non-existent directory");
    assert_test(check_dir_exist("/tmp/testbash/dir1/dir2/"), 1, "Test 10: Trailing slash on directory");

    // 11-20: Relative path tests
    assert_test(check_dir_exist("testdir"), 1, "Test 11: Relative directory path");
    assert_test(check_dir_exist("testdir/subdir"), 1, "Test 12: Relative subdirectory path");
    assert_test(check_dir_exist("testdir/file.txt"), 1, "Test 13: Relative file path");
    assert_test(check_dir_exist("testdir/newfile.txt"), 1, "Test 14: New file in relative path");
    assert_test(check_dir_exist("nonexistent/file"), 0, "Test 15: Non-existent relative path");
    assert_test(check_dir_exist("testdir/subdir/newfile"), 1, "Test 16: New file in relative subdir");
    assert_test(check_dir_exist("testdir/empty/"), 1, "Test 17: Empty directory with slash");
    assert_test(check_dir_exist("./testdir"), 1, "Test 18: Relative path with ./");
    assert_test(check_dir_exist("./testdir/subdir"), 1, "Test 19: Nested relative path with ./");
    assert_test(check_dir_exist("./nonexistent"), 0, "Test 20: Non-existent ./ path");

    // 21-30: Permission tests
    assert_test(check_dir_exist("testdir/noperm/file"), 0, "Test 21: No write permission directory");
    assert_test(check_dir_exist("/root/file"), 0, "Test 22: Root owned directory");
    assert_test(check_dir_exist("testdir/noperm"), 1, "Test 23: Read-only directory exists check");
    assert_test(check_dir_exist("/root"), 0, "Test 24: Root directory permission");
    assert_test(check_dir_exist("/etc/shadow"), 0, "Test 25: System file no permission");
    assert_test(check_dir_exist("testdir/noperm/subdir/file"), 0, "Test 26: Nested no permission");
    assert_test(check_dir_exist("/var/log/newfile"), 0, "Test 27: System directory permission");
    assert_test(check_dir_exist("testdir/noperm/"), 1, "Test 28: Read-only dir with slash");
    assert_test(check_dir_exist("./testdir/noperm/file"), 0, "Test 29: No permission with ./");
    assert_test(check_dir_exist("/etc/"), 0, "Test 30: System directory with slash");

    // 31-40: Special character tests
    assert_test(check_dir_exist("testdir/file with spaces"), 1, "Test 31: Path with spaces");
    assert_test(check_dir_exist("testdir/file_with_underscore"), 1, "Test 32: Path with underscores");
    assert_test(check_dir_exist("testdir/file.with.dots"), 1, "Test 33: Path with multiple dots");
    assert_test(check_dir_exist("testdir/file-with-dashes"), 1, "Test 34: Path with dashes");
    assert_test(check_dir_exist("testdir/!@#$%"), 1, "Test 35: Path with special chars");
    assert_test(check_dir_exist("testdir/utf8_⌘"), 1, "Test 36: Path with UTF-8");
    assert_test(check_dir_exist("testdir/quoted\"file"), 1, "Test 37: Path with quotes");
    assert_test(check_dir_exist("testdir/file(with)parentheses"), 1, "Test 38: Path with parentheses");
    assert_test(check_dir_exist("testdir/file{with}braces"), 1, "Test 39: Path with braces");
    assert_test(check_dir_exist("testdir/file[with]brackets"), 1, "Test 40: Path with brackets");

    // 41-50: Edge cases
    assert_test(check_dir_exist(""), 0, "Test 41: Empty string");
    assert_test(check_dir_exist(NULL), 0, "Test 42: NULL pointer");
    assert_test(check_dir_exist("."), 1, "Test 43: Current directory");
    assert_test(check_dir_exist(".."), 1, "Test 44: Parent directory");
    assert_test(check_dir_exist("./"), 1, "Test 45: Current directory with slash");
    assert_test(check_dir_exist("../"), 1, "Test 46: Parent directory with slash");
    assert_test(check_dir_exist("testdir//subdir"), 1, "Test 47: Double slash");
    assert_test(check_dir_exist("./././testdir"), 1, "Test 48: Multiple current dir");
    assert_test(check_dir_exist("testdir/./subdir"), 1, "Test 49: Middle current dir");
    assert_test(check_dir_exist("testdir/../testdir"), 1, "Test 50: Directory reference itself");

    // 51-60: File type tests
    assert_test(check_dir_exist("testdir/file.txt/newfile"), 0, "Test 51: File as directory");
    assert_test(check_dir_exist("/dev/null/file"), 0, "Test 52: Device as directory");
    assert_test(check_dir_exist("/etc/passwd/file"), 0, "Test 53: Regular file as directory");
    assert_test(check_dir_exist("testdir/file.txt/"), 0, "Test 54: File with trailing slash");
    assert_test(check_dir_exist("/dev/zero/"), 0, "Test 55: Device with trailing slash");
    assert_test(check_dir_exist("testdir/subdir/file.txt/"), 0, "Test 56: Nested file as directory");
    assert_test(check_dir_exist("/dev"), 1, "Test 57: Device directory");
    assert_test(check_dir_exist("/etc"), 1, "Test 58: System directory");
    assert_test(check_dir_exist("testdir/empty/newfile"), 1, "Test 59: File in empty directory");
    assert_test(check_dir_exist("/proc/self"), 1, "Test 60: Special filesystem");

    // 61-70: Path traversal tests
    assert_test(check_dir_exist("../testdir"), 1, "Test 61: Relative parent path");
    assert_test(check_dir_exist("../../testdir"), 1, "Test 62: Multiple parent directories");
    assert_test(check_dir_exist("testdir/../testdir"), 1, "Test 63: Parent in middle");
    assert_test(check_dir_exist("./testdir/../testdir/"), 1, "Test 64: Complex relative path");
    assert_test(check_dir_exist("testdir/subdir/../../testdir"), 1, "Test 65: Multiple parents middle");
    assert_test(check_dir_exist("../nonexistent"), 0, "Test 66: Non-existent parent relative");
    assert_test(check_dir_exist("testdir/subdir/../nonexistent"), 0, "Test 67: Non-existent after parent");
    assert_test(check_dir_exist("../../../"), 1, "Test 68: Many parents with slash");
    assert_test(check_dir_exist("testdir/../../../../"), 1, "Test 69: Too many parents");
    assert_test(check_dir_exist("/../../"), 1, "Test 70: Absolute with parents");

    // 71-80: Mixed path tests
    assert_test(check_dir_exist("/./tmp/./testbash"), 1, "Test 71: Absolute with current dirs");
    assert_test(check_dir_exist("/tmp/./testbash/./dir1"), 1, "Test 72: Mixed current dirs");
    assert_test(check_dir_exist("testdir/./subdir/./file"), 1, "Test 73: Relative with current dirs");
    assert_test(check_dir_exist("./testdir/../testdir/./subdir"), 1, "Test 74: Complex mixed path");
    assert_test(check_dir_exist("/tmp/../tmp/./testbash"), 1, "Test 75: Absolute mixed complex");
    assert_test(check_dir_exist("testdir/subdir/.././../testdir"), 1, "Test 76: Relative mixed complex");
    assert_test(check_dir_exist("/./nonexistent/./file"), 0, "Test 77: Non-existent mixed");
    assert_test(check_dir_exist("./testdir/nonexistent/../file"), 0, "Test 78: Non-existent mixed relative");
    assert_test(check_dir_exist("/tmp/./nonexistent/../file"), 0, "Test 79: Non-existent mixed absolute");
    assert_test(check_dir_exist("./testdir/subdir/.././file.txt"), 1, "Test 80: Existing mixed path");

    // 81-90: Symbolic link tests (if supported)
    system("ln -s testdir/file.txt testdir/link1");
    system("ln -s testdir/subdir testdir/link2");
    system("ln -s nonexistent testdir/broken_link");
    
    assert_test(check_dir_exist("testdir/link1"), 1, "Test 81: Symlink to file");
    assert_test(check_dir_exist("testdir/link2"), 1, "Test 82: Symlink to directory");
    assert_test(check_dir_exist("testdir/link2/newfile"), 1, "Test 83: File in symlinked dir");
    assert_test(check_dir_exist("testdir/broken_link"), 0, "Test 84: Broken symlink");
    assert_test(check_dir_exist("testdir/link2/"), 1, "Test 85: Symlink dir with slash");
    assert_test(check_dir_exist("./testdir/link1"), 1, "Test 86: Relative symlink to file");
    assert_test(check_dir_exist("./testdir/link2/newfile"), 1, "Test 87: Relative symlink dir file");
    assert_test(check_dir_exist("testdir/link2/../file.txt"), 1, "Test 88: Parent through symlink");
    assert_test(check_dir_exist("testdir/link2/../../testdir"), 1, "Test 89: Complex symlink path");
    assert_test(check_dir_exist("testdir/broken_link/file"), 0, "Test 90: File in broken link");

    // 91-100: Additional edge cases
    assert_test(check_dir_exist("////"), 1, "Test 91: Multiple root slashes");
    assert_test(check_dir_exist("testdir////subdir"), 1, "Test 92: Multiple middle slashes");
    assert_test(check_dir_exist("testdir/./././file.txt"), 1, "Test 93: Multiple current dirs");
    assert_test(check_dir_exist("testdir/.../file"), 0, "Test 94: Invalid dots");
    assert_test(check_dir_exist("./././"), 1, "Test 95: Only current dirs");
    assert_test(check_dir_exist("testdir/"), 1, "Test 96: Simple with trailing slash");
    assert_test(check_dir_exist("/..."), 0, "Test 97: Invalid absolute dots");
    assert_test(check_dir_exist("testdir/."), 1, "Test 98: Ending current dir");
    assert_test(check_dir_exist("testdir/.."), 1, "Test 99: Ending parent dir");
    assert_test(check_dir_exist(".././../testdir/././file.txt"), 1, "Test 100: Complex mixed all");

    // Cleanup
    system("rm -rf testdir");
    system("rm -rf /tmp/testbash");
    
    printf("\n=== Directory Check Tests Completed ===\n");
}

// Helper function to run tests
void assert_test(int result, int expected, const char *message)
{
    static int test_count = 0;
    test_count++;
    
    if (result == expected)
        printf("✓ %s\n", message);
    else
        printf("✗ %s (Expected: %d, Got: %d)\n", message, expected, result);
}