function silver_chain_organize()
    local content = darwin.mdeclare.transform_dir({
        dir="src",
        startswith="fdefine",
        endswith=".c",
    })

    darwin.dtw.write_file("src/fdeclare.all.h", content)
    darwin.silverchain.remove("src/fdeclare.all.h")

    darwin.silverchain.generate({
        src = "src",
        project_short_cut = "Quill",
        implement_main = false,

        tags = { 
            "dep_declare",
            "macros",
            "types",
            "consts",
            "fdeclare",
            'globals',
            "fdefine",
            "dep_define"
            
    }})
end 

darwin.add_recipe({
    inputs={
        "src",
        "dependencies",
        "builds"
    },
    outs= {
        "src/fdeclare.all.h"
    },
    name="silver_chain_organize",
    description = "Organize source files using SilverChain",
    callback = silver_chain_organize
})