export default function AdminHeader({ heading }) {
  return (
    <div className="mb-10">
      <div className="flex justify-center w-75%"></div>{" "}
      <h2 className="h-50 content-start flex justify-center text-2xl font-extrabold text-gray-900">
        {" "}
        {heading}{" "}
      </h2>{" "}
    </div>
  );
}
