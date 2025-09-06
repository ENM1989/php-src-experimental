/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 206d4278599ffb30b3f99ea35ff89cf35b903b52 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_ext4_defrag, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, path, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_ext4_mount_options, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, device, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_ext4_info arginfo_ext4_mount_options

ZEND_FUNCTION(ext4_defrag);
ZEND_FUNCTION(ext4_mount_options);
ZEND_FUNCTION(ext4_info);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(ext4_defrag, arginfo_ext4_defrag)
	ZEND_FE(ext4_mount_options, arginfo_ext4_mount_options)
	ZEND_FE(ext4_info, arginfo_ext4_info)
	ZEND_FE_END
};
