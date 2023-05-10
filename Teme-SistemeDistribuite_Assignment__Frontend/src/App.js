import "./App.css";
import { BrowserRouter, Routes, Route } from "react-router-dom";
import LoginPage from "./pages/Login";
import AdminPage from "./pages/AdminPage";
import CreateUserPage from "./pages/CreateUserPage";
import CreateDevicePage from "./pages/CreateDevicePage";
import ViewUsersPage from "./pages/ViewUsersPage";
import UpdateUserPage from "./pages/UpdateUserPage";
import ViewDevicePage from "./pages/ViewDevicePage";
import UpdateDevicePage from "./pages/UpdateDevicePage";
import ClientPage from "./pages/ClientPage";
import ViewDeviceForClientPage from "./pages/ViewDeviceForClientPage";
import ChatPage from "./pages/ChatPage";

function App() {
  return (
    <div className="flex items-center justify-center ">
      <div style={{ padding: "50px" }}>
        <BrowserRouter>
          <Routes>
            <Route path="/" element={<LoginPage />} />
            <Route path="/admin-page" element={<AdminPage />} />
            <Route path="/user-page" element={<CreateUserPage />} />
            <Route path="/device-page" element={<CreateDevicePage />} />
            <Route path="/view-users" element={<ViewUsersPage />} />
            <Route path="/update-page" element={<UpdateUserPage />} />
            <Route path="/view-device" element={<ViewDevicePage />} />
            <Route path="/update-page-device" element={<UpdateDevicePage />} />
            <Route path="/client-page" element={<ClientPage />} />
            <Route
              path="/client-devices"
              element={<ViewDeviceForClientPage />}
            />
            <Route path="chat-room" element={<ChatPage />} />
          </Routes>
        </BrowserRouter>
      </div>
    </div>
  );
}

export default App;
