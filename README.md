# Cinema — Cinema Management Platform

A complete cinema management system designed to automate both client-side movie browsing and server-side session control.  
The project consists of a **desktop client application (C++ / Qt)** and a **backend server (Python / Flask)** communicating via a REST API.

---

## 🛠 System Overview

### Client Side (User Interface)

- **Movie Catalog** — Displays a list of available movies with posters loaded dynamically from the server  
- **Session Selection** — View schedules, halls, and showtimes for each movie  
- **Seat Reservation** — Interactive seating layout with real-time seat availability synced with the database  
- **Responsive UI** — Interface adapts to window size by dynamically adjusting card layouts and font sizes  

### Admin Side (Management)

- **Data Control** — Create and delete movies, halls, sessions, and users  
- **Security** — Admin access protected by password authentication and IP address validation  
- **Smart Scheduling** — Server validates movie duration and prevents overlapping sessions in the same hall  
- **Database Integrity** — Deleting a movie automatically removes all related sessions and tickets  

---

## Technical Details

### Client Application (C++ / Qt 6)

- Fully asynchronous network communication (non-blocking UI)  
- Custom Qt widgets for movies, sessions, and seating layouts  
- Image processing with `Qt::SmoothTransformation` for high-quality poster rendering  

### Server Application (Python / Flask / MySQL)

- Hosted on **PythonAnywhere**  
- **Database:** MySQL with 6 core tables:
  - users  
  - admins  
  - movies  
  - halls  
  - sessions  
  - tickets  
- **REST API:** JSON-based communication secured with an API key for every request  

---

## Core API Endpoints

| Method | Endpoint | Description |
| --- | --- | --- |
| `GET` | `/getMovies` | Retrieve all available movies |
| `GET` | `/getReservePlaces` | Get seat status (0 — free, 1 — reserved) |
| `POST` | `/addSession` | Create a new session with time conflict validation |
| `POST` | `/reservePlace` | Reserve a seat |
| `POST` | `/deleteMovie` | Delete a movie and all related sessions and tickets |

---

## Running the Project

```bash
git clone git@github.com:Woratt/Cinema.git
mkdir build && cd build
cmake ..
make
