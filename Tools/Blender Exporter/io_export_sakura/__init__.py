bl_info = {
    "name":         "Sakura Game Framework Format",
    "author":       "Darrell Blake",
    "blender":      (3,4,0),
    "version":      (0,0,4),
    "location":     "File > Import-Export",
    "description":  "Export Sakura Game Framework compatible models.",
    "category":     "Import-Export"
}

if "bpy" in locals():
    import importlib
    if "export_sakura" in locals():
        importlib.reload(export_sakura)

import bpy;
from bpy_extras.io_utils import ExportHelper

class ExportSakura(bpy.types.Operator, ExportHelper):
    """Export to Sakura Game Framework format (.sak)"""
    bl_idname = "export.sakura"
    bl_label = "Export Sakura"
    
    filename_ext = ".sak"
    
    def execute(self, context):
        from . import export_sakura
        
        if bpy.ops.object.mode_set.poll():
            bpy.ops.object.mode_set(mode="OBJECT")
            
        ob = context.object
        if not ob or ob.type != "MESH":
            raise NameError("Error: Object '" + ob.name + "' is not a mesh.")
               
        return export_sakura.export_model(ob, self.filepath)

def menu_func_export(self, context):
    self.layout.operator(ExportSakura.bl_idname, text="Sakura Game Framework (.sak)")

classes = (
    ExportSakura,
)

def register():
    #bpy.utils.register_module(__name__)
    for cls in classes:
        bpy.utils.register_class(cls)
        
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)

def unregister():
    #bpy.utils.unregister_module(__name__)
    for cls in classes:
        bpy.utils.unregister_class(cls)
      
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()
