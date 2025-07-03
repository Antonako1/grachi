local main_menu = require("main_menu")
local main_game = require("main_game")

local windowWidth, windowHeight = 1024, 768
--[[

states:
    MENU
        LOAD_GAME
        START_GAME
        CONTINUE
        SETTINGS
        CREDITS
        EXIT
        MainMenu
    GAME
        ESCAPE
        SETTINGS
        LOAD_GAME
        SAVE_GAME
        QUIT_TO_MENU
        EXIT_TO_DESKTOP
        MainGame
]]--
States = {
    MENU = 1,
    GAME = 2,
}
MenuStates = {
    LOAD_GAME = 1,
    START_GAME = 2,
    CONTINUE = 3,
    SETTINGS = 4,
    CREDITS = 5,
    EXIT = 6,
    MainMenu = 7
}
GameStates = {
    ESCAPE = 1,
    SETTINGS = 2,
    LOAD_GAME = 3,
    SAVE_GAME = 4,
    QUIT_TO_MENU = 5,
    EXIT_TO_DESKTOP = 6,
    MainGame = 7
}
CurrentState = States.MENU

-- array to push pop states
InnerState = {}


function love.load()
    love.window.setTitle("Main Menu")
    love.window.setMode(windowWidth, windowHeight, {
        resizable = false,
        vsync = true,
        minwidth = 800,
        minheight = 600
    })

    main_menu.load()
    main_game.load()
end

function love.update(dt)
    if CurrentState == States.MENU then
        main_menu.update(dt)
    elseif CurrentState == States.GAME then
        main_game.update(dt)
    end
end

function love.draw()
    if CurrentState == States.MENU then
        main_menu.draw()
    elseif CurrentState == States.GAME then
        main_game.draw()
    end
end

function love.mousepressed(x, y, button, istouch)
    if CurrentState == States.MENU then
        main_menu.mousepressed(x, y, button, istouch)
    elseif CurrentState == States.GAME then
        main_game.mousepressed(x, y, button, istouch)
    end
end

function love.keypressed(key)
    if CurrentState == States.MENU then
        main_menu.keypressed(key)
    elseif CurrentState == States.GAME then
        main_game.keypressed(key)
    end
end
