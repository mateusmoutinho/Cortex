function linux_bin()
    os.execute("mkdir -p release")

    local image = darwin.ship.create_machine("alpine:latest")
    image.provider = CONTANIZER
    image.add_comptime_command("apk update")
    image.add_comptime_command("apk add --no-cache gcc g++ musl-dev curl")

    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end

    
    image.start({
        volumes = {
            {"./release", "/release"},
        },
        command = compiler .. [[ --static /release/]] .. PROJECT_NAME .. [[.c -o /release/]] .. PROJECT_NAME .. [[_linux_bin.out]]
    })

    print("\tLinux binary build completed")
end

darwin.add_recipe({
    name = "static_linux",
    requires = {"amalgamation"},
    description = "Make a static compiled linux binary of the project",
    outs = {"release/" .. PROJECT_NAME .. "_linux_bin.out"},
    inputs = {"src", "dependencies", "builds"},
    callback = linux_bin
})