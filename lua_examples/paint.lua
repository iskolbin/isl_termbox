local tb = require("termbox")

local function sparseset(t, x, y, v)
	if y < 0 then y = 67108864 + y end
	t[x*67108864 + y] = v
	return t
end

local function sparseget(t, x, y, default)
	if y < 0 then y = 67108864 + y end
	return t[x*67108864 + y] or default
end

local floor, next = math.floor, _G.next
local function sparsenext(t, prevk)
	local k, v = next(t, prevk)
	if not k then
		return
	end
	local x = floor(k/67108864)
	local y = k - x*67108864
	if y > 33554432 then
		y = y - 67108864
	end
	return k, x, y, v
end

local buffer = {}
local psw, psh = 2, 1
local runes = {' ', '░', '▒', '▓', '█'}
local curCol, curRune = 2, 5
local colors = {tb.BLACK, tb.RED, tb.GREEN, tb.YELLOW, tb.BLUE, tb.MAGENTA, tb.CYAN, tb.WHITE}
local active = true

local function updateDrawButtons(current, x, y, mx, my, n, fn)
	local lx, ly = x, y
	for i = 1, n do
		if lx <= mx and mx <= lx+3 and ly <= my and my <= ly+1 then
			current = i
		end
		local r, fg, bg = fn(i)
		tb.setcell(lx+0, ly+0, r, fg, bg)
		tb.setcell(lx+1, ly+0, r, fg, bg)
		tb.setcell(lx+2, ly+0, r, fg, bg)
		tb.setcell(lx+3, ly+0, r, fg, bg)
		tb.setcell(lx+0, ly+1, r, fg, bg)
		tb.setcell(lx+1, ly+1, r, fg, bg)
		tb.setcell(lx+2, ly+1, r, fg, bg)
		tb.setcell(lx+3, ly+1, r, fg, bg)
		lx = lx + 4
	end
	lx, ly = x, y
	for i = 1, n do
		if current == i then
			local fg, bg = tb.RED + tb.BOLD, tb.DEFAULT
			tb.setcell(lx+0, ly+2, '^', fg, bg)
			tb.setcell(lx+1, ly+2, '^', fg, bg)
			tb.setcell(lx+2, ly+2, '^', fg, bg)
			tb.setcell(lx+3, ly+2, '^', fg, bg)
		end
		lx = lx + 4
	end
	return current
end

local function runeAttrFunc(i)
	return runes[i], tb.DEFAULT, tb.DEFAULT
end

local function colorAttrFunc(i)
	return ' ', tb.DEFAULT, colors[i]
end

local function updateRedrawAll(mx, my)
	tb.clear()
	if mx ~= -1 and my ~= -1 then
		sparseset(buffer, floor(mx/psw), floor(my/psh), {runes[curRune], colors[curCol]})
	end
	for _, x, y, rc in sparsenext, buffer do
		for x_ = 0, psw-1 do
			for y_ = 0, psh-1 do
				tb.setcell(x*psw+x_, y*psh+y_, rc[1], rc[2])
			end
		end
	end
	curRune = updateDrawButtons(curRune, 0, 0, mx, my, #runes, runeAttrFunc)
	curCol = updateDrawButtons(curCol, 0, tb.height()-3, mx, my, #colors, colorAttrFunc)
	tb.present()
end

tb.init(tb.INPUT_ESC + tb.INPUT_MOUSE)

tb.setcallback(tb.EVENT_KEY, function()
	active = false
end)

tb.setcallback(tb.EVENT_MOUSE, function(mx, my, button)
	if button == tb.MOUSE_LEFT then
		updateRedrawAll(mx, my)
	end
end)

while active do
	updateRedrawAll(-1, -1)
	tb.peek()
end

tb.shutdown()
