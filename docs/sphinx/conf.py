import shutil
from cgitb import html
from datetime import date
from glob import glob

project = "Caches"
version = "0.1.0"

primary = "#4165FF"
secondary = "#914FF5"

project_copyright = f"{date.today().year} Joel Lefkowitz"

extensions = [
    "breathe",
    "myst_parser",
    "sphinxext.opengraph",
]

shutil.copytree(
    "../../docs/images",
    "../../docs/dist/docs/images",
    dirs_exist_ok=True,
)

for path in glob(f"../../*.md"):
    shutil.copyfile(
        path,
        path.replace("../..", "../dist"),
    )

myst_all_links_external = True

breathe_show_include = False
breathe_default_project = project

breathe_projects = {
    project: "../doxygen/dist",
}

breathe_default_members = (
    "members",
    "protected-members",
    "private-members",
    "undoc-members",
)

html_theme = "furo"
html_title = project
html_static_path = [""]
html_js_files = ["scripts.js"]
html_css_files = ["styles.css"]
html_theme_options = {
    "font-stack": "Space Grotesk, sans-serif",
    "font-stack--monospace": "CQ Mono, monospace",
    "light_css_variables": {
        "color-brand-content": primary,
        "color-problematic": primary,
        "color-brand-primary": secondary,
        "color-highlight-on-target": "#E0E0E0",
    },
    "dark_css_variables": {
        "color-problematic": primary,
        "color-brand-content": primary,
        "color-brand-primary": secondary,
        "color-highlight-on-target": "#202020",
    },
}
