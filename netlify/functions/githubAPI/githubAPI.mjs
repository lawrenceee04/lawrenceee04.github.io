import { Octokit } from 'octokit';

export const handler = async () => {
    const octokit = new Octokit({
        auth: process.env.VITE_GITHUB_API_KEY,
    });

    try {
        const response = await octokit.request('GET /user/repos', {
            headers: {
                'X-GitHub-Api-Version': '2022-11-28',
            },
            per_page: 100,
        });
        return {
            statusCode: 200,
            body: JSON.stringify(response.data),
        };
    } catch (error) {
        return {
            statusCode: 500,
            body: JSON.stringify({ error: 'Failed to fetch github repositories' }),
        };
    }
};
