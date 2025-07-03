local main_menu = {}

local buttons = {}
local bgImage
local font

local windowWidth, windowHeight = 1024, 768

local function createButton(text, y)
    local btnWidth, btnHeight = 300, 50
    return {
        text = text,
        x = (windowWidth - btnWidth) / 2, -- center horizontally
        y = y,
        width = btnWidth,
        height = btnHeight,
        hovered = false
    }
end

function main_menu.load()
    bgImage = love.graphics.newImage("assets/images/main_menu.png")
    font = love.graphics.newFont("assets/fonts/clacon2.ttf", 24)
    love.graphics.setFont(font)

    local startY = 200
    local gap = 70
    local labels = {"Start Game", "Continue", "Load Game", "Settings", "Credits", "Exit"}

    buttons = {}
    for i, label in ipairs(labels) do
        table.insert(buttons, createButton(label, startY + (i-1)*gap))
    end
end

function main_menu.update(dt)
    local mx, my = love.mouse.getPosition()
    for _, btn in ipairs(buttons) do
        btn.hovered = mx > btn.x and mx < btn.x + btn.width and
                      my > btn.y and my < btn.y + btn.height
    end
end

function main_menu.draw()
    -- Draw background stretched to fit window
    love.graphics.draw(bgImage, 0, 0, 0,
        windowWidth / bgImage:getWidth(),
        windowHeight / bgImage:getHeight())

    for _, btn in ipairs(buttons) do
        if btn.hovered then
            love.graphics.setColor(0.7, 0.7, 0.9, 0.9)
        else
            love.graphics.setColor(0.4, 0.4, 0.6, 0.8)
        end
        love.graphics.rectangle("fill", btn.x, btn.y, btn.width, btn.height, 8, 8)

        love.graphics.setColor(1, 1, 1)
        love.graphics.printf(btn.text, btn.x, btn.y + (btn.height - font:getHeight()) / 2, btn.width, "center")
    end
end

function main_menu.mousepressed(x, y, button, istouch)
    if button == 1 then
        for _, btn in ipairs(buttons) do
            if btn.hovered then
                print("Clicked button:", btn.text)
                if btn.text == "Exit" then
                    love.event.quit()
                elseif btn.text == "Start Game" then
                    -- Switch to game state
                    return "game"
                end
                -- Add other button handlers here
            end
        end
    end
end

function main_menu.keypressed(key)
    if key == "escape" then
        love.event.quit()
    elseif key == "return" then
        -- Handle Enter key for the first button (Start Game)
        print("Enter pressed on Start Game")
        return "game"
    end
end

return main_menu
