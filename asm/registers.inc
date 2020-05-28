
.eqv REG_JOYP, 0xFF00
.eqv _REG_JOYSTATE, 0xFF03
.eqv REG_DIV, 0xFF04
.eqv REG_TIMA, 0xFF05
.eqv REG_TMA, 0xFF06
.eqv REG_TAC, 0xFF07
.eqv _REG_DIV_OFFSET, 0xFF08

.eqv REG_TAC_STOP_BIT, 0x4
.eqv REG_TAC_CLOCK_SELECT, 0x3

.eqv REG_INTERRUPTS_REQUESTED, 0xFF0F
.eqv REG_INTERRUPTS_ENABLED, 0xFFFF

.eqv REG_LCDC, 0xFF40
.eqv REG_LCDC_LCD_ENABLE, 0x80

.eqv REG_LCDC_STATUS, 0xFF41
.eqv REG_LCDC_LYC_INT, 0x40
.eqv REG_LCDC_OAM_INT, 0x20
.eqv REG_LCDC_V_BLANK_INT, 0x10
.eqv REG_LCDC_H_BLANK_INT, 0x08
.eqv REG_LCDC_STATUS_LYC, 0x4
.eqv REG_LCDC_STATUS_MODE, 0x3
.eqv REG_LCDC_STATUS_MODE_0, 0x00
.eqv REG_LCDC_STATUS_MODE_1, 0x01
.eqv REG_LCDC_STATUS_MODE_2, 0x02
.eqv REG_LCDC_STATUS_MODE_3, 0x03

.eqv REG_LCDC_STATUS_MODE_0_CYCLES, 51
.eqv REG_LCDC_STATUS_MODE_1_CYCLES, 114
.eqv REG_LCDC_STATUS_MODE_2_CYCLES, 20
.eqv REG_LCDC_STATUS_MODE_3_CYCLES, 43

.eqv REG_SCY, 0xFF42
.eqv REG_SCX, 0xFF43
.eqv REG_LY, 0xFF44
.eqv REG_LYC, 0xFF45
.eqv REG_DMA, 0xFF46
.eqv REG_BGP, 0xFF47
.eqv REG_OBP0, 0xFF48
.eqv REG_OBP1, 0xFF49
.eqv REG_WY, 0xFF4A
.eqv REG_WX, 0xFF4B
.eqv REG_KEY1, 0xFF4D
.eqv REG_VBK, 0xFF4F

.eqv REG_SVBK, 0xFF70

.eqv INTERRUPT_V_BLANK, 0x01
.eqv INTERRUPT_LCD_STAT, 0x02
.eqv INTERRUPT_TIMER, 0x04
.eqv INTERRUPT_SERIAL, 0x08
.eqv INTERRUPT_JOYPAD, 0x10

.eqv GB_SCREEN_H, 144
.eqv GB_SCREEN_W, 160
.eqv GB_SCREEN_LINES, 154

.macro read_register_direct target, register
    lbu \target, (\register+MEMORY_MISC_START-MM_REGISTER_START)(Memory)
.endm

.macro write_register_direct target, register
    sb \target, (\register+MEMORY_MISC_START-MM_REGISTER_START)(Memory)
.endm

.macro read_register16_direct target, register
    lhu \target, (\register+MEMORY_MISC_START-MM_REGISTER_START)(Memory)
.endm

.macro write_register16_direct target, register
    sh \target, (\register+MEMORY_MISC_START-MM_REGISTER_START)(Memory)
.endm