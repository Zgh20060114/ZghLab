- kitty +kitten ssh lasm@192.168.123.196
- ssh使用本地代理:
  - `ssh -N -R 7890:localhost:7897 -p 22 zgh@192.168.123.196`
  - zgh@192.168.123.196's password: (一直挂着), 
  - 然后再ssh的服务器中bashrc中写入:`export http_proxy=http://localhost:7890` `export https_proxy=http://localhost:7890`.
- ssh的nvim无法与本地复制粘贴:
  - 在init.lua中写入:
    ~~~lua 
      if vim.env.SSH_CONNECTION then
      local ok, osc52 = pcall(require, "vim.ui.clipboard.osc52")
      if ok then
        vim.g.clipboard = {
          name = "OSC 52",
          copy = {
            ["+"] = osc52.copy("+"),
            ["*"] = osc52.copy("*"),
          },
          paste = {
            ["+"] = osc52.paste("+"),
            ["*"] = osc52.paste("*"),
          },
        }
        vim.opt.clipboard = "unnamedplus"
      end
    end
    ~~~
  - 在options.lua中写入:
      ~~~lua
      if vim.env.SSH_CONNECTION then
        vim.opt.clipboard = "unnamedplus"
      end
      ~~~
