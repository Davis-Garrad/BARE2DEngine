.PHONY: clean All

All:
	@echo "----------Building project:[ BARE2DEngine - Debug ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"
	@echo "----------Building project:[ BARETests - Debug ]----------"
	@cd "BARETests/BasicTest" && "$(MAKE)" -f  "BARETests.mk"
clean:
	@echo "----------Cleaning project:[ BARE2DEngine - Debug ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"  clean
	@echo "----------Cleaning project:[ BARETests - Debug ]----------"
	@cd "BARETests/BasicTest" && "$(MAKE)" -f  "BARETests.mk" clean
