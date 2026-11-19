/** fetch() that treats an HTTP error as an error, so a 404 page is never previewed as if it were the file. */
export async function fetchChecked(url, init) {
  const res = await fetch(url, init);
  if (!res.ok) throw new Error(`The file could not be loaded (HTTP ${res.status}).`);
  return res;
}
