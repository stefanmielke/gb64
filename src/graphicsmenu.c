
#include "graphicsmenu.h"
#include "../render.h"
#include "gameboy.h"

void renderPaletteItem(struct CursorMenuItem* menuItem, int x, int y, int selected)
{
    FONTCOL(255, 255, 255, 255);
    SHOWFONT(&glistp, menuItem->label, x, y);

    u16* paletteIndexPtr = (u16*)menuItem->data;
    u16* palette = getPalette(*paletteIndexPtr);

    if (selected)
    {
        renderSprite(&gGUIItemTemplates[GUIItemIconLeft], x, y + 12, 1, 1);
        renderSprite(&gGUIItemTemplates[GUIItemIconRight], x + 60, y + 12, 1, 1);
    }

    setSpriteColor(GET_R(palette[0]), GET_G(palette[0]), GET_B(palette[0]));
    renderSprite(&gGUIItemTemplates[GUIItemIconWhite], x + 12, y + 12, 1, 1);
    setSpriteColor(GET_R(palette[1]), GET_G(palette[1]), GET_B(palette[1]));
    renderSprite(&gGUIItemTemplates[GUIItemIconWhite], x + 24, y + 12, 1, 1);
    setSpriteColor(GET_R(palette[2]), GET_G(palette[2]), GET_B(palette[2]));
    renderSprite(&gGUIItemTemplates[GUIItemIconWhite], x + 36, y + 12, 1, 1);
    setSpriteColor(GET_R(palette[3]), GET_G(palette[3]), GET_B(palette[3]));
    renderSprite(&gGUIItemTemplates[GUIItemIconWhite], x + 48, y + 12, 1, 1);

    setSpriteColor(255, 255, 255);
}

struct MenuItem* inputPaletteItem(struct CursorMenuItem* menuItem, int buttonDown)
{
    u16* paletteIndexPtr = (u16*)menuItem->data;

    if (buttonDown & R_JPAD)
    {
        *paletteIndexPtr = (*paletteIndexPtr + 1) % getPaletteCount();
        updatePaletteInfo(&gGameboy);
    }

    if (buttonDown & L_JPAD)
    {
        if (*paletteIndexPtr == 0)
        {
            *paletteIndexPtr = getPaletteCount() - 1;
        }
        else
        {
            *paletteIndexPtr = *paletteIndexPtr - 1;
        }
        updatePaletteInfo(&gGameboy);
    }

    return NULL;
}

void graphicsMenuRender(struct MenuItem* menuItem, struct MenuItem* highlightedItem)
{
    struct GraphicsMenu* graphicsMenu = (struct GraphicsMenu*)menuItem->data;
    
    if (menuItem == highlightedItem)
    {
        gButtonSprite.alpha = 255;
        renderMenuBorder();
        FONTCOL(255, 255, 255, 255);
        SHOWFONT(&glistp, "SCREEN", 8, 32);
        renderCursorMenu(&graphicsMenu->cursor, 8, 56, 136);
    }
}

struct MenuItem* graphicsMenuHandleInput(struct MenuItem* menuItem, int buttonsDown, int buttonsState)
{
    struct GraphicsMenu* graphicsMenu = (struct GraphicsMenu*)menuItem->data;
    if (buttonsDown & INPUT_BUTTON_TO_MASK(gGameboy.settings.inputMapping.openMenu))
    {
        return graphicsMenu->cursor.parentMenu;
    }

    struct MenuItem* result = inputCursorMenu(&graphicsMenu->cursor, buttonsDown, 136);

    if (result)
    {
        return result;
    }
    else
    {
        return menuItem;
    }
}

void initGraphicsMenu(struct GraphicsMenu* menu, struct MenuItem* parentMenu)
{
    initCursorMenu(
        &menu->cursor,
        menu->menuItems,
        GraphicsMenuItemCount
    );
    menu->cursor.parentMenu = parentMenu;

    initCursorMenuItem(
        &menu->menuItems[GraphicsMenuItemGBP],
        NULL,
        "BGP",
        32
    );
    menu->menuItems[GraphicsMenuItemGBP].data = &gGameboy.settings.bgpIndex;
    menu->menuItems[GraphicsMenuItemGBP].render = renderPaletteItem;
    menu->menuItems[GraphicsMenuItemGBP].input = inputPaletteItem;
    
    initCursorMenuItem(
        &menu->menuItems[GraphicsMenuItemOBP0],
        NULL,
        "OBP0",
        32
    );
    menu->menuItems[GraphicsMenuItemOBP0].data = &gGameboy.settings.obp0Index;
    menu->menuItems[GraphicsMenuItemOBP0].render = renderPaletteItem;
    menu->menuItems[GraphicsMenuItemOBP0].input = inputPaletteItem;

    initCursorMenuItem(
        &menu->menuItems[GraphicsMenuItemOBP1],
        NULL,
        "OBP1",
        32
    );
    menu->menuItems[GraphicsMenuItemOBP1].data = &gGameboy.settings.obp1Index;
    menu->menuItems[GraphicsMenuItemOBP1].render = renderPaletteItem;
    menu->menuItems[GraphicsMenuItemOBP1].input = inputPaletteItem;
}