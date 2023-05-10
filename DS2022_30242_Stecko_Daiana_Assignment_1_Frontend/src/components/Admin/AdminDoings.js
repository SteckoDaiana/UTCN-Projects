import "../User/createUserPage.css";
import "../Device/createDevicePage.css";
import "./AdminDoings.css";

import adminService from "../../services/adminService";
import deviceService from "../../services/deviceService";

export default function AdminDoings() {
  const goToCreateDevicePage = () => {
    window.location.href = "device-page";
  };
  const deleteUserHandler = () => {
    let id = document.getElementById("idUSER").value;

    adminService.deleteProsumer(id);
    document.getElementById("idUSER").value = "";
  };
  const deleteDeviceHandler = () => {
    let id = document.getElementById("id_item").value;

    deviceService.deleteItem(id);
    document.getElementById("id_item").value = "";
  };
  const goToUpdateUserPage = () => {
    window.location.href = "update-page";
  };
  const goToUpdateDevicePage = () => {
    window.location.href = "update-page-device";
  };
  const goToLoginPage = () => {
    sessionStorage.removeItem("admUID");
    window.location.href = "/";
  };

  return (
    <div className="w-75%">
      <div className=" font-extrabold text-gray-900">
        <div>
          <button
            className="ceateUserBtn"
            onClick={() => {
              window.location.href = "user-page";
            }}
          >
            Create user
          </button>
        </div>
        <div>
          <h1 className="deleteUserLabel">Delete user by id: </h1>
          <input className="labelss" label="Delete User" id="idUSER" />
          <button className="deleteUserBtn" onClick={deleteUserHandler}>
            Delete User
          </button>
        </div>
        <div>
          <button className="updateUserBtn" onClick={goToUpdateUserPage}>
            Update User
          </button>
        </div>
        <div>
          <button
            className="viewUsersBtn"
            onClick={() => {
              window.location.href = "view-users";
            }}
          >
            View Users
          </button>
        </div>
      </div>

      <div className="font-extrabold text-gray-900">
        <div>
          <button className="ceateDeviceBtn" onClick={goToCreateDevicePage}>
            Create Device
          </button>
        </div>
        <div>
          <h1 className="deleteDeviceLabel">Delete device by id: </h1>
          <input className="labelss" label="Delete Device" id="id_item" />
          <button className="deleteDeviceBtn" onClick={deleteDeviceHandler}>
            Delete device
          </button>
        </div>

        <div>
          <button className="updateDeviceButton" onClick={goToUpdateDevicePage}>
            Update device
          </button>
        </div>
        <div>
          <button
            className="viewDeviceBtn"
            onClick={() => {
              window.location.href = "view-device";
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
