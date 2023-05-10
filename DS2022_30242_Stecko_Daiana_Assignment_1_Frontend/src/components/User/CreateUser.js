import { useState } from "react";

import * as React from "react";
import "./createUserPage.css";
import Select from "react-select";
import adminService from "../../services/adminService";

export default function CreateUser() {
  const [firstName, setFirstName] = useState("");
  const [lastName, setLastName] = useState("");
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [rolees, setRolees] = useState(0);

  const goToAdminPage = () => {
    window.location.href = "admin-page";
  };
  const insertUser = () => {
    initValues.firstName = firstName;
    initValues.lastName = lastName;
    initValues.username = username;
    initValues.password = password;
    initValues.role = rolees;
    adminService.insertProsumer(initValues);
  };

  const changeHandler1 = (event) => {
    setFirstName(event.target.value);
  };
  const changeHandler2 = (event) => {
    setLastName(event.target.value);
  };
  const changeHandler3 = (event) => {
    setUsername(event.target.value);
  };
  const changeHandler4 = (event) => {
    setPassword(event.target.value);
  };

  const initValues = {
    firstName: "",
    lastName: "",
    username: "",
    password: "",
    role: "",
  };

  const options = [
    { value: "CLIENT", label: "CLIENT" },
    { value: "ADMINISTRATOR", label: "ADMINISTRATOR" },
  ];

  return (
    <div className="w-75%">
      <div className=" font-extrabold text-gray-900">
        <div>
          <h1>First name: </h1>
          <input name="firstname" onChange={(event) => changeHandler1(event)} />
        </div>
        <div>
          <h1>Last name: </h1>
          <input name="lastname" onChange={(e) => changeHandler2(e)} />
        </div>
        <div>
          <h1>Username: </h1>
          <input name="username" onChange={(e) => changeHandler3(e)} />
        </div>
        <div>
          <h1>Password: </h1>
          <input
            type="password"
            name="password"
            onChange={(e) => changeHandler4(e)}
          />
        </div>
        <div>
          <h1>Role: </h1>

          <Select
            options={options}
            onChange={(e) => {
              setRolees(e.value);
            }}
          />
        </div>
        <div>
          <button className="insertBtn" onClick={insertUser}>
            Create User
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
