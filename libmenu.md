Turning Menu into a library

recalc() -> generate lines
repaint() -> draw and free()

can't observe data
doesn't understand data
should observe colour and config
colour -> repaint Index, IBar

If menu is separate window, with focus
how do we override / delegate key presses?

--------------------

call stack
    index
    complete
    dlgalias
    menu
    mutt_menu_loop()
    menu_dlg_dokey()
    km_do_key()
    mutt_getch()

data
    MenuData
    AliasViewArray
    AliasView
    Alias
    Menu

windows
    Dlg
        Index
        IBar

--------------------

Menu:
    Config * 10
    Colours
    Data!!!
    Windows

recalc() data, colours
repaint() draw


--------------------

Observer
    config: sort -> data -> recalc -> repaint
    colour: repaint
    alias: data -> recalc -> repaint

