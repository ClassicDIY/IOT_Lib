Import("env")
import os

src_override = env.GetProjectOption("custom_src_dir")
if src_override:
    new_src = os.path.join(env["PROJECT_DIR"], src_override)
    print(">>> Overriding PROJECT_SRC_DIR to:", new_src)
    env.Replace(PROJECT_SRC_DIR=new_src)