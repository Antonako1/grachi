local main_game = {}

function main_game.load()
    -- load game assets here
end

function main_game.update(dt)
    -- update game logic here
end

function main_game.draw()
    love.graphics.print("Game State - Press ESC to go back", 10, 10)
end

function main_game.keypressed(key)
    if key == "escape" then
        return "menu"
    end
end

return main_game
