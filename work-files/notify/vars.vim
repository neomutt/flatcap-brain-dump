QuickhlManualReset

" params
QuickhlManualAdd! \C\v(wdata\.)@<!<(buf|buflen|col|files|flags|m|multiple|numfiles|state)>

" state
QuickhlManualAdd! \v<(ch|mbstate|rc|width|win)>

" locals
QuickhlManualAdd! \C\v(wdata\.)@<!<(first|hclass|pass|redraw|tempbuf|templen)>

QuickhlManualAdd! \v<wdata\.(buf|buflen|col|files|flags|m|multiple|numfiles|state|first|hclass|pass|redraw|tempbuf|templen)>
