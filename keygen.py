import tkinter as tk
from tkinter import ttk, messagebox
from cryptography.hazmat.primitives.asymmetric import rsa, dsa
from cryptography.hazmat.primitives import serialization


def generate_keys():
    key_name = keyname_entry.get().strip()
    key_length = int(keylength_entry.get().strip())
    key_type = keytype_combo.get()

    if not key_name:
        messagebox.showerror("Error", "Enter key name")
        return

    if key_type == "RSA":
        private_key = rsa.generate_private_key(
            public_exponent=65537,
            key_size=key_length
        )

    elif key_type == "DSA":
        private_key = dsa.generate_private_key(
            key_size=key_length
        )

    else:
        messagebox.showerror("Error", "Select key type")
        return

    public_key = private_key.public_key()

    private_pem = private_key.private_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PrivateFormat.PKCS8,
        encryption_algorithm=serialization.NoEncryption()
    )

    public_pem = public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    )

    with open(f"{key_name}_private.pem", "wb") as f:
        f.write(private_pem)

    with open(f"{key_name}_public.pem", "wb") as f:
        f.write(public_pem)

    messagebox.showinfo(
        "Success",
        f"Keys generated:\n{key_name}_private.pem\n{key_name}_public.pem"
    )


root = tk.Tk()
root.title("Key Generator")
root.geometry("350x250")

tk.Label(root, text="Key Name").pack(pady=5)
keyname_entry = tk.Entry(root, width=30)
keyname_entry.pack()

tk.Label(root, text="Key Length").pack(pady=5)
keylength_entry = tk.Entry(root, width=30)
keylength_entry.insert(0, "2048")
keylength_entry.pack()

tk.Label(root, text="Key Type").pack(pady=5)
keytype_combo = ttk.Combobox(root, values=["RSA", "DSA"], state="readonly")
keytype_combo.set("RSA")
keytype_combo.pack()

tk.Button(root, text="Generate Keys", command=generate_keys).pack(pady=20)

root.mainloop()