vim.lsp.config('clangd', {
    settings = {
        ['clangd'] = { '--compile-commands-dir=build/main.release', '--query-driver=/opt/devkitpro/devkitARM/bin/arm-none-eabi-g++' },
    },
})
vim.defer_fn(function()
    vim.cmd(":LspRestart")
end, 0)
