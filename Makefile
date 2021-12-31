.PHONY: clean All

All:
	@echo "----------Building project:[ BARE2DEngine - Debug ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"
	@echo "----------Building project:[ BARETest_ThreeBody - Debug ]----------"
	@cd "BARETests/Orbiter" && "$(MAKE)" -f  "BARETest_ThreeBody.mk"
clean:
	@echo "----------Cleaning project:[ BARE2DEngine - Debug ]----------"
	@"$(MAKE)" -f  "BARE2DEngine.mk"  clean
	@echo "----------Cleaning project:[ BARETest_ThreeBody - Debug ]----------"
	@cd "BARETests/Orbiter" && "$(MAKE)" -f  "BARETest_ThreeBody.mk" clean
