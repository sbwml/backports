@r@
identifier OPS;
identifier platform_driver_remove;
fresh identifier platform_driver_remove_wrap = "bp_" ## platform_driver_remove;
position p;
@@
+#if LINUX_VERSION_IS_LESS(6,11,0)
+static int platform_driver_remove_wrap(struct platform_device *pdev)
+{
+	platform_driver_remove(pdev);
+
+	return 0;
+}
+#endif

struct platform_driver OPS@p = {
+#if LINUX_VERSION_IS_GEQ(6,11,0)
	.remove = platform_driver_remove,
+#else
+	.remove = platform_driver_remove_wrap,
+#endif
};
