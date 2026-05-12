import tkinter as tk
from tkinter import filedialog, messagebox
import json
import hashlib
import base64

from cryptography.hazmat.primitives import hashes, serialization
from cryptography.hazmat.primitives.asymmetric import padding, rsa, dsa
from cryptography.exceptions import InvalidSignature


def browse_file():
    path = filedialog.askopenfilename()
    file_entry.delete(0, tk.END)
    file_entry.insert(0, path)


def browse_metadata():
    path = filedialog.askopenfilename(filetypes=[("JSON files", "*.json")])
    metadata_entry.delete(0, tk.END)
    metadata_entry.insert(0, path)


def browse_public_key():
    path = filedialog.askopenfilename(filetypes=[("PEM files", "*.pem")])
    key_entry.delete(0, tk.END)
    key_entry.insert(0, path)


def verify_file():
    file_path = file_entry.get().strip()
    metadata_path = metadata_entry.get().strip()
    public_key_path = key_entry.get().strip()

    if not file_path or not metadata_path or not public_key_path:
        messagebox.showerror("Error", "Select file, metadata, and public key")
        return

    try:
        with open(file_path, "rb") as f:
            file_data = f.read()

        with open(metadata_path, "r") as f:
            metadata = json.load(f)

        with open(public_key_path, "rb") as f:
            public_key = serialization.load_pem_public_key(f.read())

        calculated_hash = hashlib.sha256(file_data).hexdigest()
        stored_hash = metadata["file_hash"]

        if calculated_hash != stored_hash:
            messagebox.showerror(
                "Verification Failed",
                "File hash mismatch"
            )
            return

        signature = base64.b64decode(metadata["signature"])

        if isinstance(public_key, rsa.RSAPublicKey):
            public_key.verify(
                signature,
                file_data,
                padding.PKCS1v15(),
                hashes.SHA256()
            )

        elif isinstance(public_key, dsa.DSAPublicKey):
            public_key.verify(
                signature,
                file_data,
                hashes.SHA256()
            )

        else:
            messagebox.showerror(
                "Verification Failed",
                "Unsupported public key type"
            )
            return

        messagebox.showinfo(
            "Verification Success",
            "File Verified Successfully"
        )

    except InvalidSignature:
        messagebox.showerror(
            "Verification Failed",
            "Invalid digital signature"
        )

    except Exception as e:
        messagebox.showerror("Error", str(e))


root = tk.Tk()
root.title("File Verifier")
root.geometry("600x280")

tk.Label(root, text="File to Verify").pack(pady=5)
file_entry = tk.Entry(root, width=75)
file_entry.pack()
tk.Button(root, text="Browse File", command=browse_file).pack(pady=3)

tk.Label(root, text="Metadata File").pack(pady=5)
metadata_entry = tk.Entry(root, width=75)
metadata_entry.pack()
tk.Button(root, text="Browse Metadata", command=browse_metadata).pack(pady=3)

tk.Label(root, text="Public Key").pack(pady=5)
key_entry = tk.Entry(root, width=75)
key_entry.pack()
tk.Button(root, text="Browse Public Key", command=browse_public_key).pack(pady=3)

tk.Button(root, text="Verify File", command=verify_file).pack(pady=20)

root.mainloop()