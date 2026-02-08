
function local_linux_bin_build()
    
    local dependencies_files = darwin.dtw.list_files("dependencies", false)
    darwin.dtw.create_dir_recursively("libs")
    for i=1, #dependencies_files do
        local file = dependencies_files[i]
        if string.sub(file, -2) == ".c" then
            local out = string.sub(file, 1, -2)
            local command = "gcc -c dependencies/"..file.." -o libs/"..out.."o"
            print("command: ", command) 
            os.execute(command)
        end
    end

    local build_props = {
        cflags = CFLAGS or ""
    }

    local compiler = "gcc"
    if LAUNGUAGE == "cpp" then
        compiler = "g++"
    end
   
    local compilation = compiler.." "..build_props.cflags.." -o app main.c "
    for i=1, #dependencies_files do
        local file = dependencies_files[i]
        if string.sub(file, -2) == ".c" then
            local out = string.sub(file, 1, -2)
            compilation = compilation.." libs/"..out.."o"
        end
    end
    compilation = compilation.." -ldl"
    print("compilation: ", compilation) 
    os.execute(compilation)

    print("\tLocal Linux binary build completed")
end

darwin.add_recipe({
    inputs={
        "dependencies",
        "src",
        "builds",
        "libs"
    },
    outs= {
        "app"
    },
    name="local_unix_bin",
    description = "Build static object files and link them into a local Linux binary",
    callback = local_linux_bin_build
})