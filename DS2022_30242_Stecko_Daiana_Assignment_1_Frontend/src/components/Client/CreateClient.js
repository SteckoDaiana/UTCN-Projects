import "../User/createUserPage.css";
import "../Device/createDevicePage.css";
import "./CreateClient.css";
import "../Chat/chatRoom.css";

import adminService from "../../services/adminService";
import deviceService from "../../services/deviceService";
import clientService from "../../services/clientService";

export default function CreateClient() {
  const deleteUserHandler = () => {
    let id = document.getElementById("idUSER").value;

    adminService.deleteProsumer(id);
    document.getElementById("idUSER").value = "";
  };

  const goToLoginPage = () => {
    sessionStorage.removeItem("admUID");
    window.location.href = "/";
  };

  return (
    <div className="w-75%">
      <div className=" font-extrabold text-gray-900"></div>

      <div className="font-extrabold text-gray-900">
        <div>
          <button
            className="viewDeviceBtn"
            onClick={() => {
              window.location.href = "client-devices";
            }}
          >
            View devices
          </button>
        </div>
        <div>
          <button
            className="chatBtn"
            onClick={() => {
              window.location.href = "chat-room";
            }}
          >
            Chat
          </button>
        </div>
        <button className="backBtn" onClick={goToLoginPage}>
          Go back
        </button>
      </div>
    </div>
  );
}
