function debug_run()

    local size = darwin.argv.get_flag_size({ "target" })
    local debug_is_present = false
    for i=1,size do
        local target = darwin.argv.get_flag_arg_by_index({ "target" }, i)
        if target == "debug" then
            debug_is_present = true
        end
    end    
    if not debug_is_present then
        return
    end
    os.execute("kill -9 $(lsof -t -i:3000) 2>/dev/null; fuser -k 3000/tcp 2>/dev/null")
    os.execute("CWebStudioFirmware --port " .. PORT .. " --dynamic_lib debug.so --callback main_internal_server_firmware --password whatever &")
    local old_hash = ""
    while true do
        local changes_hasher = darwin.dtw.newHasher()
        changes_hasher.digest_file("main.c")
        changes_hasher.digest_file("app.c")
        local new_hash = changes_hasher.get_value()
        if old_hash ~= new_hash then
            print("Building debug.so")
            embed_assets()
            os.execute(COMPILER.." -shared -fPIC main.c -o debug.so")
            if not darwin.dtw.isfile("debug.so") then
                print("Failed to build debug.so")
            end
        end
        
        old_hash = new_hash
    end 


end

darwin.add_recipe({
    name = "debug",
    description = "Make hot  reload debug run",
    outs = {"debug.so"},
    inputs = {"main.c", "app.c", "dependencies","builds"},
    callback = debug_run
})