import { useState } from "react";
import * as React from "react";
import deviceService from "../../services/deviceService";

export default function CreateDevice() {
  //const [id_item, setId] = useState("");
  const [description, setDescription] = useState("");
  const [adress, setAdress] = useState("");
  const [consumption, setConsumption] = useState("");
  const [username, setUsername] = useState("");
  const goToAdminPage = () => {
    window.location.href = "admin-page";
  };
  const initValues = {
    description: "",
    adress: "",
    consumption: "",
    username: "",
  };
  const insertDevice = () => {
    initValues.description = description;
    initValues.adress = adress;
    initValues.consumption = consumption;
    initValues.username = username;

    console.log(initValues);
    deviceService.insertItem(initValues);
  };

  const changeHandler1 = (event) => {
    setDescription(event.target.value);
  };

  const changeHandler2 = (event) => {
    setAdress(event.target.value);
  };
  const changeHandler3 = (event) => {
    setConsumption(event.target.value);
  };
  const changeHandler4 = (event) => {
    setUsername(event.target.value);
  };

  return (
    <div className="w-75%">
      <div className=" font-extrabold text-gray-900">
        <div>
          <h1>Description: </h1>
          <input
            name="description"
            onChange={(event) => changeHandler1(event)}
          />
        </div>
        <div>
          <h1>Adress: </h1>
          <input name="adress" onChange={(event) => changeHandler2(event)} />
        </div>
        <div>
          <h1>Consumption: </h1>
          <input
            name="consumption"
            onChange={(event) => changeHandler3(event)}
          />
        </div>
        <div>
          <h1>Username: </h1>
          <input name="username" onChange={(event) => changeHandler4(event)} />
        </div>

        <div>
          <button className="insertBtn" onClick={insertDevice}>
            Create Device
          </button>
        </div>
        <div>
          <button className="backBtn" onClick={goToAdminPage}>
            Go back
          </button>
        </div>
      </div>
    </div>
  );
}
