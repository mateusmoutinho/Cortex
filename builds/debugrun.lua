function debug_run()


    if not darwin.argv.flags_exist({ "debug" }) then
        return
    end

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