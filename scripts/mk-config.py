#!/usr/bin/env python

import click
import jinja2
import yaml

PKG_TPL = "configs/packages.yaml.j2"
CFG_TPL = "configs/tion.yaml.j2"


@click.command()
@click.option("--verbose", "-v", count=True)
@click.option("--define", "-D", multiple=True)
def main(verbose: int, define: tuple[str]):
    defines: dict[str, str] = {}
    for d in define:
        k, v = d.split("=")
        defines[k.strip()] = v.strip()

    if "enabled_packages" in defines:
        defines["enabled_packages"] = [
            item.strip() for item in defines["enabled_packages"].split(",")
        ]

    env = jinja2.Environment(loader=jinja2.FileSystemLoader("."))
    template = env.get_template(PKG_TPL)
    packages = template.render(**defines)
    packages = yaml.safe_load(packages)
    for key, pkg in packages.items():
        if "enabled" not in pkg or key in defines.get("enabled_packages", []):
            pkg["enabled"] = True

    template = env.get_template(CFG_TPL)
    rendered = template.render(packages=packages, **defines)
    print(rendered)


if __name__ == "__main__":
    # pylint: disable=no-value-for-parameter
    main()
