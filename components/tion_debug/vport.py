import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

# pylint: disable-next=relative-beyond-top-level
from .. import tion, vport

AUTO_LOAD = ["vport", "tion"]

TionHostVPort = tion.tion_ns.class_("TionHostVPort", cg.PollingComponent, vport.VPort)
TionHostIO = tion.tion_ns.class_("TionLtHostIO")

CONFIG_SCHEMA = vport.vport_schema(TionHostVPort, TionHostIO)


async def to_code(config):
    # await vport.setup_vport_uart(config)
    vio = cg.new_Pvariable(config[vport.CONF_VPORT_IO_ID])
    var = cg.new_Pvariable(config[CONF_ID], vio)
    await cg.register_component(var, config)

    cg.add_define("USE_VPORT_HOST")
    cg.add_define("USE_VPORT_UART")
    cg.add_define("USE_TION_LT")
