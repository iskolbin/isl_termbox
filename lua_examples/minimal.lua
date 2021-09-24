local tb = require("termbox")

local active = true

tb.init(tb.INPUT_ESC + tb.INPUT_MOUSE)

tb.setcallback(tb.EVENT_KEY, function(ch, code, mod)
	active = false
end)

tb.setcallback(tb.EVENT_RESIZE, function(w, h)
end)

tb.setcallback(tb.EVENT_MOUSE, function(x, y, button)
	if button == tb.MOUSE_LEFT then
	end
end)

local function update()
	tb.clear()
	tb.present()
end

while active do
	update()
	tb.peek()
end

tb.shutdown()
