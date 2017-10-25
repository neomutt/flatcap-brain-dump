syn clear

let end = getpos('$')

for i in range (1, end[1], 2)
	execute 'syntax match green  ''\%' . i . 'l.*'''
	let j = i + 1
	execute 'syntax match cyan   ''\%' . j . 'l.*'''
endfor
