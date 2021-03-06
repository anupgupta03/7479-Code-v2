/**
 * @Date:   2016-11-30T10:50:44+11:00
* @Last modified time: 2016-12-02T22:23:42+11:00
 */
#include "../include/main.h"
#include "../include/menuControl.h"
#include "string.h"

// Storage for our menus, choices and lists
menuList Lists[MAX_MEN_LISTS];
menu Menus[MAX_MENUS];
clist MenuChoices[MAX_CHOICES];

// Indexes for next item to be allocated
static int nl = 0;
static int nm = 0;
static int nc = 0;

menuList* menuListInit() {
	  menuList* list = &(Lists[nl++]);

	  list->first = NULL;
	  list->last = NULL;
	  list->num = 0;

	  return (list);
}

int menuListAddMenu(menuList* list, menu* m) {
	  menu* TopMenu;
	  menu* EndMenu;

	  if (list == NULL || m == NULL) return NULL;

	  if (list->num == 0) {
		    // first entry
		    list->first = m;
		    list->last = m;

		    // double linked list that we want to rate so pint at ourself
		    m->next = (menu*)m;
		    m->prev = (menu*)m;
	  } else {
		    // get the menus at start and end of the list
		    TopMenu = list->first;
		    EndMenu = list->last;

		    // Add to end of list
		    m->prev = EndMenu;
		    m->next = list->first;

		    // relink the list
		    EndMenu->next = m;
		    TopMenu->prev = m;

		    // this menu is now the last one
		    list->last = m;
	  }

	  // make new menu current menu
	  list->current = m;

	  // one more entry
	  list->num++;

	  return (list->num);
}

menu* menuInit(menuList* list, const char* name, int type, int max, unsigned func) {
	  menu* m;

	  // We have no malloc so use allocate from an array
	  m = &(Menus[nm++]);

	  // LCD line 1 display
	  sprintf(&(m->lcd_line_1[0]), "%s", name);

	  // Default for LCD line 2 display
	  switch (type) {
	  case MENUTYPE_SUB:
		    sprintf(&(m->lcd_line_2[0]), SUBMENU_SELECT_TEXT);
		    break;

	  case MENUTYPE_EXIT:
		    sprintf(&(m->lcd_line_2[0]), EXIT_MENU_SELECT);
		    break;

	  default:
		    sprintf(&(m->lcd_line_2[0]), DEFAULT_LINE2);
		    break;
	  }

	  // note menu type
	  m->menu_type = type;

	  // default values
	  m->value = 0;
	  m->max_value = max;

	  // no choices yet
	  m->cfirst = NULL;
	  m->cend = NULL;
	  m->cnum = 0;

	  // no sub menu yet
	  m->list = NULL;

	  // link into list
	  menuListAddMenu(list, m);

	  // return pointer to this menu
	  return (m);
}

clist* MenuAddChoice(menu* m, const char* name) {
	  clist* c;
	  clist* end;

	  // check for null pointer
	  if (m == NULL) return NULL;

	  // We have no malloc so use allocate from an array
	  c = &(MenuChoices[nc++]);

	  // first choice
	  if (m->cnum == 0) {
		    m->cfirst = c;
		    m->cend = c;
		    c->prev = (clist*)NULL;
		    c->next = (clist*)NULL;
	  } else {
		    // subsequent choices
		    end = m->cend;

		    // only link to end - this list is not circular
		    m->cend = c;
		    end->next = c;

		    c->prev = end;
		    c->next = (clist*)NULL;
	  }

	  // copy name for this choice
	  sprintf(&(c->name[0]), "%s", name);

	  // one more
	  m->cnum++;

	  // return pointer to the choice
	  return (c);
}

int menuLcdUpdate(menu* m) {
	  if (m == NULL) return NULL;
	  lcdClear(LCD_PORT);
	  lcdPrint(LCD_PORT, 1, m->lcd_line_1);
	  lcdPrint(LCD_PORT, 2, m->lcd_line_2);
	  return RETURN_SUCCESS;
}

int menuCreateValueDisplay(menu* m) {
	  if (m == NULL) return NULL;
	  sprintf(&(m->lcd_line_2[0]), "<<    %04d    >>", m->value);
	  return RETURN_SUCCESS;
}

int menuCreateChoiceDisplay(menu* m) {
	  int i, len;
	  clist* c;

	  if (m == NULL || (c = m->cfirst) == NULL) return NULL;

	  // move through list to find indexd choice
	  for (i = 0; i < m->value; i++) {
		    if (c->next != NULL) c = c->next;
	  }

	  // get length of choice
	  len = strlen(&(c->name[0]));

	  // Make string with the arrows at each end
	  sprintf(&(m->lcd_line_2[0]), "<<            >>");

	  // len needs to be 12 or less
	  if (len > 12) len = 12;

	  // overlay choice to display
	  for (i = 0; i < len; i++) {
		    m->lcd_line_2[2 + (6 - (len + 1) / 2) + i] = c->name[i];

	  }
	  return RETURN_SUCCESS;
}

int menuCreateDisplay(menu* m) {
	  if (m == NULL) return NULL;
	  if (m->menu_type == MENUTYPE_VALUE)
		    menuCreateValueDisplay(m);
	  else if (m->menu_type == MENUTYPE_CHOICE)
		    menuCreateChoiceDisplay(m);
	  return RETURN_SUCCESS;
}

int menuRun(menuList* list) {
	  if (list == NULL) return NULL;
	  bool done = false;
	  int LcdButtons;
	  userControl buttonState = initializeButton;

	  while (!done) {
		    // Read LCD buttons
		    LcdButtons = lcdReadButtons(LCD_PORT);

		    switch (buttonState) {
		    case initializeButton:
		    case leftButtonDown:
		    case rightButtonDown:
		    case centerButtonDown:
			      // Display select program
			      menuCreateDisplay(list->current);
			      menuLcdUpdate(list->current);

			      // Wait here until nothing is pressed
			      if (LcdButtons == 0) buttonState = noButton;
			      break;

		    case noButton:
			      // Check left button
			      if (LcdButtons & LCD_BTN_LEFT) {
					buttonState = leftButtonDown;
					// previous menu
					if (list->current->prev != NULL) list->current = list->current->prev;
			      }

			      // Check right button
			      if (LcdButtons & LCD_BTN_RIGHT) {
					buttonState = rightButtonDown;
					// next menu
					if (list->current->next != NULL) list->current = list->current->next;
			      }

			      // Check center button
			      if (LcdButtons & LCD_BTN_CENTER) {
					buttonState = centerButtonDown;
					switch (list->current->menu_type) {
					case MENUTYPE_EXIT:
						  // An exit menu - we are done
						  done = true;
						  break;
					case MENUTYPE_VALUE:
						  // increase value
						  list->current->value++;
						  // check for max and wrap around
						  if (list->current->value > list->current->max_value) list->current->value = 0;
						  break;
					case MENUTYPE_CHOICE:
						  // value is used as an index
						  list->current->value++;
						  // check for end of choice list and wrap
						  if (list->current->value >= list->current->cnum) list->current->value = 0;
						  // invoke(list->current->func);
						  // printf("CLICK");
						  // printf("%d", globalAutonFunction);
						  break;
					case MENUTYPE_SUB:
						  // selection using a sub menu
						  if (list->current->list != NULL) {
							    // recursively enter menu run for sub menu
							    menuRun(list->current->list);
							    // now change the menu name to match the selection
							    strcpy(list->current->lcd_line_1, list->current->list->current->lcd_line_1);
						  }
						  break;
					default:
						  break;
					}
			      }
			      break;

		    default:
			      // why are we even here ??
			      buttonState = noButton;
			      break;
		    }

		    // 50mS Delay
		    delay(50);
	  }

	  return RETURN_SUCCESS;
}

void mainMenuInit() {
	  menuList* mainMenu = menuListInit();
	  menuList* autonomousSubMenu = menuListInit();
	  menu* m;

	  lcdInit(LCD_PORT);
	  lcdSetBacklight(LCD_PORT, true);

	  m = menuInit(mainMenu, "Reset Sensors", MENUTYPE_CHOICE, 0, FUNC_RESET_SENSORS);
	  m = menuInit(mainMenu, "Reset FUNC", MENUTYPE_CHOICE, 0, FUNC_RESET_FUNCTIONALITY);

	  // Autonomous menu - has sub menu
	  m = menuInit(mainMenu, "Auton Mode", MENUTYPE_SUB, 0, NULL);
	  m->list = autonomousSubMenu;

	  // Sub menu for autonomous selection
	  menuInit(autonomousSubMenu, "LEFT P", MENUTYPE_CHOICE, 0, FUNC_AUTON_LEFT_PRIMARY);
	  menuInit(autonomousSubMenu, "RIGHT P", MENUTYPE_CHOICE, 0, FUNC_AUTON_RIGHT_PRIMARY);
	  menuInit(autonomousSubMenu, "PRGM SKILLS", MENUTYPE_CHOICE, 0, FUNC_PROGRAMMING_SKILLS);

	  // An exit menu - Done and run code
	  menuInit(mainMenu, "DONE", MENUTYPE_EXIT, 0, NULL);

	  // Start menus
	  menuRun(mainMenu);

	  // menu system done so do something
	  lcdClear(LCD_PORT);

	  lcdSetText(LCD_PORT, 1, "Exited Menu");
}
