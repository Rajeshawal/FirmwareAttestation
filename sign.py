import tkinter as tk
from tkinter import filedialog, messagebox
import json
import hashlib
import base64
import os

from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding, rsa, dsa


def browse_file():
    file_path = filedialog.askopenfilename()
    file_entry.delete(0, tk.END)
    file_entry.insert(0, file_path)


def browse_private_key():
    key_path = filedialog.askopenfilename(filetypes=[("PEM files", "*.pem")])
    key_entry.delete(0, tk.END)
    key_entry.insert(0, key_path)


def sign_file():
    file_path = file_entry.get().strip()
    private_key_path = key_entry.get().strip()
    version = version_entry.get().strip()

    if not file_path or not private_key_path or not version:
        messagebox.showerror("Error", "Select file, private key, and enter version")
        return

    try:
        with open(file_path, "rb") as f:
            file_data = f.read()

        with open(private_key_path, "rb") as f:
            private_key = serialization.load_pem_private_key(
                f.read(),
                password=None
            )

        file_hash = hashlib.sha256(file_data).hexdigest()

        if isinstance(private_key, rsa.RSAPrivateKey):
            signature = private_key.sign(
                file_data,
                padding.PKCS1v15(),
                hashes.SHA256()
            )
            key_type = "RSA"

        elif isinstance(private_key, dsa.DSAPrivateKey):
            signature = private_key.sign(
                file_data,
                hashes.SHA256()
            )
            key_type = "DSA"

        else:
            messagebox.showerror("Error", "Unsupported private key type")
            return

        metadata = {
            "filename": os.path.basename(file_path),
            "version": version,
            "hash_algorithm": "SHA256",
            "file_hash": file_hash,
            "signature_algorithm": f"{key_type}-SHA256",
            "signature": base64.b64encode(signature).decode()
        }

        output_path = file_path + ".metadata.json"

        with open(output_path, "w") as f:
            json.dump(metadata, f, indent=4)

        messagebox.showinfo("Success", f"Metadata created:\n{output_path}")

    except Exception as e:
        messagebox.showerror("Error", str(e))


root = tk.Tk()
root.title("File Signer")
root.geometry("550x310")

tk.Label(root, text="File to Sign").pack(pady=5)
file_entry = tk.Entry(root, width=70)
file_entry.pack()
tk.Button(root, text="Browse File", command=browse_file).pack(pady=3)

tk.Label(root, text="Private Key").pack(pady=5)
key_entry = tk.Entry(root, width=70)
key_entry.pack()
tk.Button(root, text="Browse Private Key", command=browse_private_key).pack(pady=3)

tk.Label(root, text="Firmware / File Version").pack(pady=5)
version_entry = tk.Entry(root, width=70)
version_entry.insert(0, "1.0.0")
version_entry.pack()

tk.Button(
    root,
    text="Sign File and Generate Metadata",
    command=sign_file
).pack(pady=20)

root.mainloop()