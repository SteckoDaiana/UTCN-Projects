import Header from "../components/Admin/AdminHeader";
import AdminDoings from "../components/Admin/AdminDoings";

import LoginPage from "./Login";
function AdminPage() {
  return (
    <>
      <Header heading="Welcome back to our dear manager !" />

      <div className=" flex justify-center  font-extrabold text-gray-900">
        <h1>There is a list of things you can do: </h1>
      </div>

      <AdminDoings />
    </>
  );
}

export default sessionStorage.getItem("admUID") ? AdminPage : LoginPage;
