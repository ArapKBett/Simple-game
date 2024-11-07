// game.js
const ffi = require('ffi-napi');

const gameEngine = ffi.Library('./game_engine.so', {
    'GameEngine_new': ['pointer', []],
    'GameEngine_init': ['bool', ['pointer', 'string', 'int', 'int']],
    'GameEngine_handleEvents': ['void', ['pointer']],
    'GameEngine_update': ['void', ['pointer']],
    'GameEngine_render': ['void', ['pointer']],
    'GameEngine_clean': ['void', ['pointer']],
    'GameEngine_running': ['bool', ['pointer']],
});

const engine = gameEngine.GameEngine_new();
if (gameEngine.GameEngine_init(engine, 'My Game', 800, 600)) {
    const gameLoop = () => {
        if (gameEngine.GameEngine_running(engine)) {
            gameEngine.GameEngine_handleEvents(engine);
            gameEngine.GameEngine_update(engine);
            gameEngine.GameEngine_render(engine);
            setImmediate(gameLoop);
        } else {
            gameEngine.GameEngine_clean(engine);
        }
    };
    gameLoop();
} else {
    console.error('Failed to initialize the game engine.');
}
