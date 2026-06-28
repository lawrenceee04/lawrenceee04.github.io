const GITHUB_API_BASE = 'https://api.github.com';
const GRAVATAR_API_BASE = 'https://api.gravatar.com/v3/profiles';

const jsonResponse = (body, status = 200) =>
  new Response(JSON.stringify(body), {
    status,
    headers: { 'Content-Type': 'application/json' },
  });

export default {
  async fetch(request, env) {
    const url = new URL(request.url);
    const pathname = url.pathname.replace(/\/$/, '');

    if (pathname === '/api/github') {
      return handleGitHubRequest(request, env, url);
    }

    if (pathname === '/api/gravatar') {
      return handleGravatarRequest(request, env, url);
    }

    return new Response('Not found', { status: 404 });
  },
};

async function handleGitHubRequest(request, env, url) {
  if (request.method !== 'GET') {
    return jsonResponse({ error: 'Method not allowed' }, 405);
  }

  const numOfRepos = Number(url.searchParams.get('numOfRepos') ?? '3');
  const headers = {
    Accept: 'application/vnd.github+json',
    'X-GitHub-Api-Version': '2022-11-28',
  };

  if (env.GITHUB_API_KEY) {
    headers.Authorization = `Bearer ${env.GITHUB_API_KEY}`;
  }

  try {
    const response = await fetch(
      `${GITHUB_API_BASE}/user/repos?sort=updated&per_page=${numOfRepos}`,
      { headers }
    );

    const data = await response.json();
    return new Response(JSON.stringify(data), {
      status: response.status,
      headers: { 'Content-Type': 'application/json' },
    });
  } catch (error) {
    return jsonResponse({ error: 'Failed to fetch GitHub repositories' }, 500);
  }
}

async function handleGravatarRequest(request, env, url) {
  if (request.method !== 'GET') {
    return jsonResponse({ error: 'Method not allowed' }, 405);
  }

  const profileIdentifier = url.searchParams.get('profileIdentifier');
  if (!profileIdentifier) {
    return jsonResponse({ error: 'Missing profileIdentifier query parameter' }, 400);
  }

  const headers = { Accept: 'application/json' };
  if (env.GRAVATAR_API_KEY) {
    headers.Authorization = `Bearer ${env.GRAVATAR_API_KEY}`;
  }

  try {
    const response = await fetch(`${GRAVATAR_API_BASE}/${profileIdentifier}`, {
      method: 'GET',
      headers,
    });

    const data = await response.json();
    return new Response(JSON.stringify(data), {
      status: response.status,
      headers: { 'Content-Type': 'application/json' },
    });
  } catch (error) {
    return jsonResponse({ error: 'Failed to fetch avatar data' }, 500);
  }
}
