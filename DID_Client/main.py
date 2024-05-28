from tkinter import Tk, Label, Button, Entry, Frame, messagebox, Text
from weidentityService import weidentityService
from weidentityClient import weidentityClient
from PIL import Image, ImageTk
import numpy as np
import pickle
import random
import cv2
import os

didURL = "https://did.moonkey.top:6001"
weidService = weidentityService(didURL)
weidClient = weidentityClient(didURL)
privKey = "0xc4a116fb87ae9b8b87842b0f46e1bbf71c37fdae1104fd6d3fd2041e23c8c68e"
nonce = str(random.randint(1, 999999999999999999999999999999))

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
recognizer = cv2.face.LBPHFaceRecognizer_create()
if os.path.exists("face_data.pkl"):
    with open("face_data.pkl", "rb") as f:
        face_data = pickle.load(f)
    if face_data:
        faces, ids = [], []
        for username, user_data in face_data.items():
            faces.extend(user_data["face_features"])
            ids.extend([user_data["id"]] * len(user_data["face_features"]))
        recognizer.train(faces, np.array(ids))
else:
    face_data = {}


def save_faces():
    with open("face_data.pkl", "wb") as f:
        pickle.dump(face_data, f)
    if face_data:
        faces, ids = [], []
        for username, user_data in face_data.items():
            faces.extend(user_data["face_features"])
            ids.extend([user_data["id"]] * len(user_data["face_features"]))
        recognizer.train(faces, np.array(ids))


def quitProgram():
    exit(0)


class FaceApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Face Recognition Login")
        self.root.geometry("800x600")
        self.camera = cv2.VideoCapture(0)
        self.camera_label = Label(self.root)
        self.camera_label.pack()
        self.main_frame = Frame(self.root)
        self.main_frame.pack(pady=20)
        self.username_label = Label(self.main_frame, text="Enter Username:")
        self.username_label.grid(row=0, column=0)
        self.username_entry = Entry(self.main_frame)
        self.username_entry.grid(row=0, column=1)
        self.register_button = Button(self.main_frame, text="Exit", command=quitProgram)
        self.register_button.grid(row=1, column=0)
        self.register_button = Button(self.main_frame, text="Register", command=self.register_face)
        self.register_button.grid(row=1, column=1)
        self.login_button = Button(self.main_frame, text="Login", command=self.login_face)
        self.login_button.grid(row=1, column=2)
        self.update_camera()

    def update_camera(self):
        if hasattr(self, 'camera_label'):
            ret, frame = self.camera.read()
            if ret:
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                faces = face_cascade.detectMultiScale(gray, 1.3, 5)
                for (x, y, w, h) in faces:
                    cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
                frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
                img = Image.fromarray(frame)
                imgtk = ImageTk.PhotoImage(image=img)
                self.camera_label.imgtk = imgtk
                self.camera_label.configure(image=imgtk)
            self.root.after(10, self.update_camera)

    def stop_camera_update(self):
        if hasattr(self, 'camera_label'):
            self.camera_label.pack_forget()

    def register_face(self):
        username = self.username_entry.get()
        if username == "":
            messagebox.showerror("Error", "Username cannot be empty")
            return
        count = 0
        face_id = len(face_data) + 1
        face_data[username] = {"id": face_id, "face_features": []}
        while True:
            ret, frame = self.camera.read()
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            faces = face_cascade.detectMultiScale(gray, 1.3, 5)
            for (x, y, w, h) in faces:
                cv2.rectangle(frame, (x, y), (x + w, y + h), (255, 0, 0), 2)
                face_roi = gray[y:y + h, x:x + w]
                if count % 5 == 0:
                    face_data[username]["face_features"].append(face_roi)
                count += 1
            if count >= 20:
                break
        save_faces()
        recognizer.train([face for user in face_data for face in face_data[user]["face_features"]],
                         np.array(
                             [face_data[user]["id"] for user in face_data for _ in face_data[user]["face_features"]]))
        messagebox.showinfo("Success", "User registered successfully")

    def login_face(self):
        ret, frame = self.camera.read()
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.3, 5)
        for (x, y, w, h) in faces:
            face_roi = gray[y:y + h, x:x + w]
            label, confidence = recognizer.predict(face_roi)
            for user, info in face_data.items():
                if info["id"] == label:
                    self.welcome_user(user)
                    return
        messagebox.showerror("Error", "Face not recognized")

    def welcome_user(self, username):
        self.main_frame.pack_forget()
        self.stop_camera_update()
        self.user_frame = Frame(self.root)
        self.user_frame.pack(pady=20)
        Label(self.user_frame, text=f"Welcome, {username}!").pack(pady=20)
        self.input_entry = Entry(self.user_frame, width=100)
        self.input_entry.pack(pady=(0, 20))
        self.info_text = Text(self.root, height=20, width=100)
        self.info_text.pack(pady=(10, 0))
        self.info_text.insert("end", "System Configuration and Information:\n")
        self.info_text.insert("end", "Configuration details and system logs will appear here.")
        top_row = Frame(self.user_frame)
        top_row.pack(pady=(0, 10))
        bottom_row = Frame(self.user_frame)
        bottom_row.pack(pady=(10, 0))
        parent = top_row
        Button(parent, text="CreateDID", command=lambda i=1: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="GetDID", command=lambda i=2: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="CreateIssuer", command=lambda i=3: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="GetIssuer", command=lambda i=4: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="CreateCPT", command=lambda i=5: self.button_action(i)).pack(side="left", padx=5)
        parent = bottom_row
        Button(parent, text="GetCPT", command=lambda i=6: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="CreateCredential", command=lambda i=7: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="VerifyCredential", command=lambda i=8: self.button_action(i)).pack(side="left", padx=5)
        Button(parent, text="getRegisteredEndpoint", command=lambda i=9: self.button_action(i)).pack(side="left",
                                                                                                     padx=5)
        Button(parent, text="getEndpoint", command=lambda i=10: self.button_action(i)).pack(side="left", padx=5)
        Button(self.user_frame, text="Logout", command=self.logout).pack(pady=10)

    def button_action(self, index):
        user_input = self.input_entry.get()
        btnName = ['', 'CreateDID', 'GetDID', 'CreateIssuer', 'GetIssuer', 'CreateCPT', 'GetCPT', 'CreateCredential',
                   'VerifyCredential', 'getRegisteredEndpoint', 'getEndpoint']
        if user_input == '':
            user_input = 'NULL ARGV'
        self.info_text.insert("end", f"\n{btnName[index]} requested with argv: {user_input}\n")
        res = 'NULL RES'
        # argvList = ['', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '']
        argvList = user_input.split(';')
        try:
            if index == 1:
                res = weidService.create_weidentity_did()
            elif index == 2:
                res = weidService.get_weidentity_did(argvList[0])
            elif index == 3:
                res = weidService.create_authority_issuer(argvList[0], argvList[1], argvList[2])
            elif index == 4:
                res = weidService.get_authority_issuer(argvList[0], argvList[1], argvList[2])
            elif index == 5:
                res = weidService.create_cpt(argvList[0], argvList[1], argvList[2])
            elif index == 6:
                res = weidService.get_cpt(argvList[0])
            elif index == 7:
                res = weidService.create_credential(argvList[0], argvList[1], argvList[2], argvList[3], argvList[4])
            elif index == 8:
                res = weidService.verify_credential(argvList[0], argvList[1], argvList[2], argvList[3], argvList[4],
                                                    argvList[5], argvList[6], argvList[7])
            elif index == 9:
                res = weidService.get_registered_endpoint()
            elif index == 10:
                res = weidService.get_endpoint(argvList[0])
            print(res)
            self.info_text.insert("end", f"\n{res}\n")
        except Exception as e:
            print(e)
            self.info_text.insert("end", f"\nERROR: {e}\n")

    def logout(self):
        self.user_frame.pack_forget()
        self.info_text.pack_forget()
        self.camera_label.pack()
        self.main_frame.pack(pady=20)


root = Tk()
app = FaceApp(root)
root.mainloop()
