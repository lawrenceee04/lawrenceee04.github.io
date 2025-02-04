import fetch from 'node-fetch';

export const handler = async (event) => {
    const profileIdentifier = event.headers.profileidentifier;
    const apiKey = process.env.VITE_GRAVATAR_API_KEY;

    try {
        const response = await fetch(`https://api.gravatar.com/v3/profiles/${profileIdentifier}`, {
            method: 'GET',
            headers: {
                Authorization: `Bearer ${apiKey}`,
            },
        });
        const data = await response.json();
        return {
            statusCode: 200,
            body: JSON.stringify(data),
        };
    } catch (error) {
        return {
            statusCode: 500,
            body: JSON.stringify({ error: 'Failed to fetch avatar' }),
        };
    }
};
