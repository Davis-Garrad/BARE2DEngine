.PHONY: clean All

All:
	@echo "----------Building project:[ BARE2DEngine - Release ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"
	@echo "----------Building project:[ BAREXML - Release ]----------"
	@cd "BARETests/BAREXML" && "$(MAKE)" -f  "BAREXML.mk"
clean:
	@echo "----------Cleaning project:[ BARE2DEngine - Release ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"  clean
	@echo "----------Cleaning project:[ BAREXML - Release ]----------"
	@cd "BARETests/BAREXML" && "$(MAKE)" -f  "BAREXML.mk" clean
