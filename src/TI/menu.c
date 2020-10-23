#include "menu.h"

short menu_display()
{
    HANDLE menu = MenuNew(2, LCD_WIDTH, 18);
    HANDLE menu_exec;

    MenuAddText(menu, MENU_ROOT, "file", MENU_FILE, 0);
    MenuAddText(menu, MENU_FILE, "load matrix", MENU_FILE_LOAD_MATRIX, 0);

    MenuAddText(menu, MENU_ROOT, "draw", MENU_DRAW, 0);
    MenuAddText(menu, MENU_DRAW, "draw graph", MENU_DRAW_GRAPH, 0);
    MenuAddText(menu, MENU_DRAW, "transitive closure", MENU_DRAW_TRANSITIVE_CLOSURE, 0);
    MenuAddText(menu, MENU_DRAW, "move node", MENU_DRAW_NODE_MOVE, 0);
    MenuAddText(menu, MENU_DRAW, "move set coords", MENU_DRAW_NODE_SET_COORDS, 0);
    MenuAddText(menu, MENU_DRAW, "rename node", MENU_DRAW_RENAME_NODE, 0);
    MenuAddText(menu, MENU_DRAW, "display weight", MENU_DRAW_DISPLAY_WEIGHT, 0);

    MenuAddText(menu, MENU_ROOT, "display", MENU_DISPLAY, 0);
    MenuAddText(menu, MENU_DISPLAY, "matrix", MENU_DISPLAY_MATRIX, 0);
    MenuAddText(menu, MENU_DISPLAY, "vertices", MENU_DISPLAY_EDGES, 0);
    MenuAddText(menu, MENU_DISPLAY, "nodes", MENU_DISPLAY_NODES, 0);
    MenuAddText(menu, MENU_DISPLAY, "previous dictionary", MENU_DISPLAY_PREV_DICT, 0);
    MenuAddText(menu, MENU_DISPLAY, "next dictionary", MENU_DISPLAY_NEXT_DICT, 0);
    MenuAddText(menu, MENU_DISPLAY, "matrix power", MENU_DISPLAY_MATRIX_POWER, 0);
    MenuAddText(menu, MENU_DISPLAY, "transitive closure", MENU_DISPLAY_TRANSITIVE_CLOSURE, 0);
    MenuAddText(menu, MENU_DISPLAY, "find path", MENU_DISPLAY_FIND_PATH, 0);

    MenuAddText(menu, -1, "quit", MENU_QUIT, 0);

    menu_exec = MenuBegin(HeapDeref(menu), 0, 0, 0);
    return MenuKey(menu_exec, GKeyIn(NULL, 0));
}
