.PHONY: clean All

All:
	@echo "----------Building project:[ BARE2DEngine - Release ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"
clean:
	@echo "----------Cleaning project:[ BARE2DEngine - Release ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk" clean
