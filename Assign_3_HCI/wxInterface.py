import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk, UnidentifiedImageError
import requests
from io import BytesIO

# Function to fetch and display images from URLs
def load_image(url, size):
    try:
        # Fetch the image data
        response = requests.get(url)
        
        # Check if the request was successful
        if response.status_code != 200:
            print(f"Failed to load image from {url}. Status code: {response.status_code}")
            return None
        
        img_data = response.content
        
        # Try to open the image with Pillow
        img = Image.open(BytesIO(img_data))
        img = img.resize(size, Image.ANTIALIAS)
        return ImageTk.PhotoImage(img)
    except UnidentifiedImageError:
        print(f"Cannot identify image from {url}")
        return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

# Define the main application window
root = tk.Tk()
root.title("Myntra Homepage Clone")
root.geometry("1200x700")  # Set the window size

# Set background color (similar to Myntra's white scheme)
root.configure(bg='white')

# Create a frame for the navigation bar
navbar_frame = tk.Frame(root, bg='#FF3F6C', height=50)
navbar_frame.pack(fill='x')

# Add buttons to the navbar (Home, Men, Women, Kids, etc.)
navbar_buttons = ['Home', 'Men', 'Women', 'Kids', 'Beauty', 'Studio']
for button in navbar_buttons:
    btn = tk.Button(navbar_frame, text=button, bg='#FF3F6C', fg='white', font=('Arial', 12, 'bold'), bd=0)
    btn.pack(side='left', padx=15, pady=10)

# Create a frame for the main content (where images will be displayed)
content_frame = tk.Frame(root, bg='white')
content_frame.pack(pady=20)

# Load images from the URLs
image_urls = [
    'images/Img.jpg',  # Replace with the actual paths to your images
    'images/hero_image2.jpg',
    'images/hero_image3.jpg'
]

# Create a grid to display the images
for idx, url in enumerate(image_urls):
    img_label = tk.Label(content_frame, bg='white')
    img_label.grid(row=0, column=idx, padx=10)
    
    # Load and set the image
    img = load_image(url, (300, 200))
    if img:

        img_label.config(image=img)
        img_label.image = img  # Keep a reference to avoid garbage collection

# Start the Tkinter event loop
root.mainloop()
