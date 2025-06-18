#!/usr/bin/env python

import click
import jinja2
import yaml

PKG_TPL = "configs/packages.yaml.j2"
CFG_TPL = "configs/tion.yaml.j2"


@click.command()
@click.argument("vars_yaml")
@click.option("--verbose", "-v", count=True)
@click.option("--define", "-D", multiple=True)
def main(vars_yaml, verbose: int, define: tuple[str]):
    defines = {}
    for d in define:
        a = d.split("=")
        defines[a[0].strip()] = a[1].strip()

    with open(vars_yaml, "r") as file:
        vars = yaml.safe_load(file)

    env = jinja2.Environment(loader=jinja2.FileSystemLoader("."))
    template = env.get_template(PKG_TPL)
    packages = template.render(**vars, **defines)
    packages = yaml.safe_load(packages)
    for pkg in packages.values():
        if "enabled" not in pkg:
            pkg["enabled"] = True

    template = env.get_template(CFG_TPL)
    rendered = template.render(packages=packages, **vars, **defines)
    print(rendered)


if __name__ == "__main__":
    # pylint: disable=no-value-for-parameter
    main()
