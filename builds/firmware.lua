function firmware_build()

    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end

    os.execute(compiler .. " -shared -o " .. "release/" .. PROJECT_NAME .. ".so" .."release/"..PROJECT_NAME..".c" )
end

darwin.add_recipe({
    name = "firmware",
    description = "Make a single so to be used combined with CWebStudioFirmware",
    outs = {"release/" .. PROJECT_NAME .. ".so"},
    inputs = {"main.c", "app.c", "dependencies","builds"},
    requires={"amalgamation"},
    callback = firmware_build
})