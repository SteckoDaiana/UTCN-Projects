import React, { useEffect, useState } from "react";
import adminService from "../services/adminService";
import LoginPage from "./Login";

function ViewUsersPage() {
  const [allUsers, setAllUsers] = useState([]);
  useEffect(() => {
    getUsers();
  }, []);
  const goToAdminPage = () => {
    window.location.href = "admin-page";
  };

  async function getUsers() {
    let datas = await adminService.getPersons();
    setAllUsers(datas.data);
    console.log(datas.data);
  }

  return (
    <div>
      <table className="table">
        <thead>
          <tr>
            <th>Id</th>
            <th>Last Name</th>
            <th>First Name</th>
            <th>Username</th>
            <th>Role</th>
          </tr>
        </thead>
        <tbody>
          {allUsers.map((data) => {
            return (
              <tr key={data.id}>
                <td>{data.id}</td>
                <td>{data.lastName}</td>
                <td>{data.firstName}</td>
                <td>{data.username}</td>
                <td>{data.role}</td>
              </tr>
            );
          })}
        </tbody>
      </table>
      <div>
        <button className="backBtn" onClick={goToAdminPage}>
          Go back
        </button>
      </div>
    </div>
  );
}
export default sessionStorage.getItem("admUID") ? ViewUsersPage : LoginPage;
