PROJECT_NAME = "Segfault-as-a-Service"
CONTANIZER   = darwin.argv.get_flag_arg_by_index({ "provider", "contanizer" }, 1, "podman")
VERSION      = "0.1.0"
LICENSE      = "Unlicense"
URL          = "https://github.com/mateusmoutinho/Segfault-as-a-Service"
DESCRIPITION = "Segfault-as-a-Service - C-Based Web Server Template for vibecoding"
FULLNAME     = "Mateus Moutinho"
EMAIL        = "[EMAIL_ADDRESS]"
SUMARY       = "Segfault-as-a-Service - C-Based Web Server Template for vibecoding"
LANGUAGE     = "c"

-- Load all build recipes from builds/ directory
darwin.load_all("builds")