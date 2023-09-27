import os

def build_project(name: str):
    command = "g++ -o %s.exe -O2 -s " % name

    for entry in os.scandir("project/impl"):
        if not entry.is_file() or not entry.name.endswith((".cc", ".cpp")):
            continue
        
        command += "\"%s\" " % entry.path
    
    command += "\"project/main.cc\""
    
    os.system(command)

build_project("pang")
