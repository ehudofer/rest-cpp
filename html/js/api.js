let token = null;

export function setToken(t) {
  token = t;
}

export async function api(url, options = {}) {
  const res = await fetch(url, {
    ...options,
    headers: {
      'Content-Type': 'application/json',
      ...(options.headers || {}),
      ...(token ? { Authorization: `Bearer ${token}` } : {})
    }
  });

  if (res.status === 401) {
    // logout / redirect
    throw new Error('unauthorized');
  }

  return res.json();
}

export async function login(username, password) {
  const res = await api('/api/login', {
    method: 'POST',
    body: JSON.stringify({ username, password })
  });

  setToken(res.token);
  state.user = res.user;
  load();
}